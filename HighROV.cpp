#include "HighROV.h"
#include "PWMController.h"
#include "Networking.h"
#include "Data.h"
#include "Thrusters.h"
#include "RotaryCameras.h"
#include "DepthSensor.h"
#include "Manipulator.h"
#include "Config.h"
#include "IMUSensor.h"
#include "AnalogSensors.h"
#include "Debug.h"
#include "USB/USBAPI.h"

rov::RovControl control;
rov::RovTelemetry Telemetry;

bool wait_for_serial = 1; // change to 1 to enable waiting for serial connection for <wait_for_serial_time> milliseconds
int wait_for_serial_time = 15000; //milliseconds

void setup() {
    Wire.begin();
    Wire.setTimeout(1000);
    Wire.setClock(10000);

    delay(100);

    SerialUSB.begin(115200);
    unsigned int t_on = millis();
    while(!SerialUSB && wait_for_serial){
      if(millis() >= t_on + wait_for_serial_time){  
        break;
      }else{
        analogWrite(LED_BUILTIN, sin(millis() * 0.03) * 127 + 127);
        delay(1);
      }
    }
    if(wait_for_serial){
      delay(200);
    }			analogWrite(LED_BUILTIN, 255);

    // Serial.begin(115200);
    // Serial1.begin(115200);

    HighROV::init();
}



void loop() {
    HighROV::run();
}

void HighROV::init() {
	using namespace config::debug;
	SerialUSB.println("HighROV init!");

	pinMode(LED_BUILTIN, OUTPUT);
	analogWrite(LED_BUILTIN, 100);

	PWMController::init();
	if(!standalone || force_ethernet_init)
		Networking::init();
	else
		SerialUSB.println("Ethernet support disabled");
	Thrusters::init();
	RotaryCameras::init();
	if(!standalone || force_depth_sensor_init)
		DepthSensor::init();
	else
		SerialUSB.println("Depth sensor support disabled");;
	Manipulator::init();
	IMUSensor::init();
	AnalogSensors::init();
	if(!standalone)
		delay(3000);
}

void gracefulReset(){
	SerialUSB.end();
	Wire.end();
	IMUSensor::end();
	NVIC_SystemReset();
}

void serialHandler(){
	if(SerialUSB.available()){
		String msg = SerialUSB.readString();
		msg.trim();
		if(msg=="reset"){
			SerialUSB.println("Resetting the controller, please reconnect the debug cable or reactivate serial monitor if you want to continue debugging");
			gracefulReset();
		}
		else
			if(msg=="debug")
                Debug::debugMenu();
			else
				SerialUSB.println("send \"reset\" for controller reset or \"debug\" for debug menu");
	}
}

void HighROV::run() {
		using namespace config;
		using namespace pwm;
		serialHandler();
		AnalogSensors::update();
		if (!config::debug::standalone || config::debug::force_ethernet_init) {
			Networking::maintain();
		}

		Telemetry.yaw = IMUSensor::getYaw();
		Telemetry.roll = IMUSensor::getRoll();
		Telemetry.pitch = IMUSensor::getPitch();
		Telemetry.depth = DepthSensor::getDepth();
		Telemetry.temperature = DepthSensor::getTemp();
		Telemetry.ammeter = AnalogSensors::getAmperage();
		Telemetry.voltmeter = AnalogSensors::getVoltage();
		Telemetry.cameraIndex = RotaryCameras::get_cam_index();


		Networking::read_write_udp(Telemetry, control);
		Thrusters::update_thrusters(control, Telemetry);

		RotaryCameras::set_angle(config::servos::front, constrain(control.cameraRotation[0], -1, 1) * 3.0);
		RotaryCameras::set_angle(config::servos::back,  constrain(control.cameraRotation[1], -1, 1) * 3.0);
		RotaryCameras::select_cam(control.cameraIndex == 1 ? true : false);

		Manipulator::set_power(control.manipulatorRotation, control.manipulatorOpenClose);

		if (DepthSensor::getUpdateStatus() == true) {
			analogWrite(LED_BUILTIN, sin(millis() * 0.01) * 127 + 127);
		} else {
			analogWrite(LED_BUILTIN, 255);
		}
        Debug::debugHandler(control);
}

