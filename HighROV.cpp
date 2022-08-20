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
#include "USB/USBAPI.h"

bool standalone = 1;//turn on when debugging only the board without ROV
bool force_ethernet_init = 0;//turn on only when debugging ethernet without ROV
bool force_depth_sensor_init = 0; //turn on when debugging depth sensor without ROV
rov::RovControl control;
rov::RovTelemetry Telemetry;
int manip_speed = 30;//percent
int manip_pos = -100;//default position
uint8_t debug_mode = 0b00000000;


String ayana[] = {
"	oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo++oooooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo:. +ooooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo:..~..ooooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooo+:++oooooooooooooooooooooooooo:...+~ .:oooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooo+. .:~~~~~:~::+++++:::~::::::....~o+~.~oooooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooo+..~++:...        .   .      .~.+oo+.~oooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooo:. ~oo+:.~.      ..... ..    ..+oo+..oooooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooooo~. +ooo:.. ........... ......:o+o: ~oooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooooo~ +oo+:.....~..~...~.~~.~~..:+oo~ :oooooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooooooo:.:+~...~~~.~~..~~~~..~~~.. ~++...oooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooooooo+~~~ .....~.:~~~~~...~... . ...  +ooooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooooooooo+~..  . .....~~.~.. ........  ..~ooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooooooo+~~:.... .....~.....~:+++:~..   ..ooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooooooo:.:~.~.~.....~~~~~.~+~.~......    +oooooooooooooooooooo\n\
	ooooooooooooooooooooooooooooooooooooooooooooo...~..~+~~~:~:~~~~~oo+  ~.~....   +oooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooooooo+ ......~~.~~:~~~:~:++++.~~~...    .oooooooooooooooooooo\n",
"	oooooooooooooooooooooooooooooooooooooooooooo~  ...~:+. ~+++++++.   ..~~.. .     +ooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooooo+:..  ...+o+++ooooooo+:::+~~~. ..     :ooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooooo:...   ..~++++o+ooo+o+++++~~~. .   .   ooooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooooo+~.....~. ..+ooooo+oooo+o+++~~. .    .  ::oooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooooo++++++++oo+:..~++ooo+++ooooo+:~..     ... o:+ooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooooooo+:++oo+oooo++o+.~::++++oo++:~~:..   . . ..:.+o~ooooooooooooooooo\n\
	oooooooooooooooooooooooooooooooo++.~:oo+o+++++++++:~..           .~~. ........:+~o+:oooooooooooooooo\n\
	ooooooooooooooooooooooooooo+++:..~:+ooo+++++++++++~. .   ~+~.~::: ~+:::~.  ...~o:+o~:ooooooooooooooo\n\
	ooooooooooooooooooooooo+::.....:++oooo++++++ooo+o+~~.. .~++++++~  ++ooo+. .....+++oo :oooooooooooooo\n\
	ooooooooooooooooooo+:.     . .+oooo++++:++o++oo+:. ..~:.:++:~....:o:+++o+... ..:o:oo+ :ooooooooooooo\n\
	ooooooooooooooo+:.  .~:+~..:++ooooooo++++o++::~.~.~:+~.~~~:..~...~++++++o+.. . .++:oo+ ~oooooooooooo\n\
	oooooooooooo+:  .:++oo+~:+oo+++oo++o+o++::...~++o+~++:~:~~~~~:~.:+++o++oo+~. ~: ~o~+oo+ .+oooooooooo\n\
	o+oooooooo+:  .+oooo+~~ooo++++++o+++++~ . .:+oooo+:+:~::++++:.~+o++++++o++....o+.~+.ooo+::+ooooooooo\n\
	o++oooooo+.  ~+oooo+.+o+::::~~~:~~:+o~ .~~o+o++o++:::+~:+:~~.~ooo++:+o++++: . +oo:~ :ooo+o+++ooooooo\n\
	oo+:+ooo+. .~+oo++:..~.~~~..     .~:++.+:o+++++o+++:++::~...~oo+oo++++++++~ . ~oooo..+ooooo+++++oooo\n\
	oooo+~::...:~+~.       .~.  .....    ~:o++++++++++:+++++....+ooo++:+o+++o:  .. +ooo~ :::+ooooo+~~++o\n\
	oooooo+~..+:~    ..          ...      .~~:+++++++++++++::. ~++++++:++oo++ ..  ..:oo: :++~.~++o::o+.~\n",
"	ooooooo+~~o:~ .......     ...~...        ~:::+++++++++:+:  .+++++:+++++++~....~. .+~ ~ooo+~ .~.+oo+.\n\
	oooooooo++o:. .........   ..~....     ..  .++++++++++++++. ~~++::+o+o++++:~...o+......:++++.  +oooo+\n\
	oooooooo++: ..  .... ...  .... ..      .. ..:+++++++++++++::+:+::+o++ooo+::~. ~oo:.... .:+++~.+ooooo\n\
	oooooooo+. .   .......   ..~~....      ......~++++++++++++++++:+++o++o+o+:::.  +oo~ .....~:o+:oooooo\n\
	ooooooo+  .  .:  ... ... .....~.         . .. .:+++oo+++++:::::oo+oooo++:::::~ .+o. ...~.  ..+oooooo\n\
	oooooo+~ . .+oo~ ....... ......       . ..~...  ~ooo+o++++.~+:+oo++++:~~~~::~+. .:   +: ~. . .~+oooo\n\
	oooooo+~  ~oooo+ ......  .......        ........ .++o+o+++~.::+oo+~:~:~.~:~~~:+. .   oo+... . +~:+oo\n\
	ooooooo. :oooooo: .. ..  ~.~... .       ........~  ~++++o+~ :+:oo+::~:~~~:~~~~+:   .:~+o+~. . :o++++\n\
	oooo+oo::ooooooo+   .    ..... .         ... . ...  .+++++~ ~+++oo:~~~~.+~~~~.:+ ...~.~~:~.....ooooo\n\
	ooo+:ooooooooo+..~  ..   .....          .......~...   :+o++:++++oo:~~~~ +~~~~~:~   .. ::::~~.. +oooo\n\
	oooo+:++++++~~~++o+      ...              ...~.... .  ~.+oo++++:oo+~~~..+~.~~. .. ...  ~:+~:.. +oooo\n\
	oooooo++++++ooooooo.    ....              . ..... ..  .~ :+o++:+oo+~~~..o.~~...~... .. ~:.~:~. ooooo\n\
	oooooooooooooooooooo.    .                  .......    ~. .+o+++ooo..~ :o.....::~...~. ~o+~~~ :ooooo\n\
	oooooooooooooooooooo+                      ....... .  .~.~ .+++++oo~...o+ .~.:o+:~.~~   o++~..oooooo\n\
	ooooooooooooooooooooo~                       ...  ... ~~~.  ~o++ooo~..:o~...~+o+:~~~.   o++:. oooooo\n\
	ooooooooooooooooooooo+                            .   .~. .  :+ooo+...o:.. ~+o+:++:~~  :o:+: ~+ooooo\n",
"	ooooooooooooooooooooo:                                 ...~ .+oooo+..+:~~.~oo++++::+~  ++++::~+ooooo\n\
	oooooooooooooooooooo+                                  :~..:oooooo~.+~+:~+oooooooo.~  +oooo++:+ooooo\n\
	ooooooooooooooooooo~.         ..                       .. .oooooo+~oo+oooooooooo+.   +oooooooooooooo\n\
	oooooooooooooooooo~             :~::++:~::~.  ..      .~   .oooo+:oooooooooooo+~    +ooooooooooooooo\n\
	ooooooooooooooooo~              ~oooooooooo++++++++:++oo.   .+oooooooooooooo+~    ~ooooooooooooooooo\n\
	oooooooooooooooo:     ~          +ooooooooooooooooooooooo.    ~+ooooooo++~..    ~+oooooooooooooooooo\n\
	ooooooooooooooo+ .   ..          .oooooooooooooooooooooooo+.     ....        ~+ooooooooooooooooooooo\n\
	oooooooooooooo+. .                +ooooooooooooooooooooooooo+~.         .~:+oooooooooooooooooooooooo\n\
	oooooooooooo+~ ... .   . .        ooooooooooooooooooooooooooooo++++++++ooooooooooooooooooooooooooooo\n\
	ooooooooooo+..... .   ~o+        ~oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\
	ooooooooooo~ .... ..  +oo.   ..   oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\
	ooooooooooo+~       ~+ooo. ..     +ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\
	ooooooooooooo+::::++ooooo~. .     ~ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\
	ooooooooooooooooooooooooo~ ..     ~ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\
	ooooooooooooooooooooooooo+.      ~oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\
	ooooooooooooooooooooooooooo+~.~~+ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n"
};



void HighROV::init() {
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

	delay(3000);
}

void thruster_debug(rov::RovControl &ctrl) {
		using namespace config;

		PWMController::set_thruster(thrusters::horizontal_front_left,  ctrl.thrusterPower[0]);
		PWMController::set_thruster(thrusters::horizontal_front_right, ctrl.thrusterPower[1]);
		PWMController::set_thruster(thrusters::horizontal_back_left,   ctrl.thrusterPower[2]);
		PWMController::set_thruster(thrusters::horizontal_back_right,  ctrl.thrusterPower[3]);
		PWMController::set_thruster(thrusters::vertical_front,         ctrl.thrusterPower[4]);
		PWMController::set_thruster(thrusters::vertical_back,          ctrl.thrusterPower[5]);

		PWMController::set_servo_power(servos::front,  ctrl.thrusterPower[6]);
		PWMController::set_servo_power(servos::back,   ctrl.thrusterPower[7]);
		PWMController::set_servo_power(servos::pwm_a2, ctrl.thrusterPower[8]);
		PWMController::set_servo_power(servos::pwm_a3, ctrl.thrusterPower[9]);
}

void gracefulReset(){
	SerialUSB.end();
	Wire.end();
	IMUSensor::end();
	NVIC_SystemReset();
}

void debugMenu(){
	SerialUSB.print("Debug menu:\n"\
					"1 - analog sensors\n"\
					"2 - depth sensor\n"\
					"3 - IMU\n"\
					"4 - manipulator\n"\
					"5 - networking\n"\
					"6 - thrusters\n"\
					"7 - reset\n"\
					"8 - neko\n"\
					"0 - exit\n"\
					"Currently flags are: 0x");
	SerialUSB.println(debug_mode, BIN);
	SerialUSB.print("Your choice: ");
	while (!SerialUSB.available());

	String msg = SerialUSB.readString();
	msg.trim();
	SerialUSB.println(msg);
	int debug_curr = msg.toInt();
	if(debug_curr==8){
		SerialUSB.println("Hi, I'm your ROV's neko girl, Ayana, and I am responsible for debugging all of this, nya!\n");
		for(int i = 0; i<4; i++){
			SerialUSB.print(ayana[i]);
		}
		return;
	}
	if(debug_curr<=0 || debug_curr>7){
		SerialUSB.println("wrong input, please resend the input one number at a time");
		return;
	}
	if (debug_curr == 2 && (standalone && !force_depth_sensor_init)) {
		SerialUSB.println("Depth sensor is disabled, please change config variables 'bool standalone' and 'bool force_depth_sensor_init'");
	}
	if (debug_curr == 5 && (standalone && !force_ethernet_init)) {
		SerialUSB.println("Ethernet stack is disabled, please change config variables 'bool standalone' and 'bool force_ethernet_init'");
		return;
	}

	bitToggle(debug_mode, debug_curr);
	SerialUSB.println(debug_mode);
}

void serialHandler(){
	if(SerialUSB.available()){
		String msg = SerialUSB.readString();
		msg.trim();
		if(msg=="reset"){
			SerialUSB.print("Resetting the controller, please reconnect the debug cable or serial monitor if you want to continue debugging");
			gracefulReset();
		}
		else
			if(msg=="debug")
				debugMenu();
			else
				SerialUSB.println("send \"reset\" for controller reset or \"debug\" for debug menu");
	}
}

void debugHandler(){
	using namespace config::debug;
	if(bitRead(debug_mode, debug_type_bits::analog_sensors)==1)//analog sensors debug
	{
		SerialUSB.println("[analog sensors debug]		Amperage:		" + String(AnalogSensors::getAmperage()) + "\n"\
							"                     			Voltage: 		" + String(AnalogSensors::getVoltage()));
	}
	if(bitRead(debug_mode, debug_type_bits::depth_sensor)==1)//depth sensor debug
	{
		SerialUSB.println("[depth sensor debug] 			Depth:			" + String(AnalogSensors::getAmperage()) + "\n");
	}
	if(bitRead(debug_mode, debug_type_bits::imu)==1)//IMU debug
	{
		SerialUSB.println("[IMU debug] 					Yaw/Roll/Pitch:	" + String(IMUSensor::getYaw(), 2) + "/" + String(IMUSensor::getRoll(),2) + "/" + String(IMUSensor::getPitch()));
	}
	if(bitRead(debug_mode, debug_type_bits::manipulator)==1)//Manipulator debug
	{
		SerialUSB.println("[Manipulator debug] 			Position:		" + String(manip_pos));
		// SerialUSB.println("[Manipulator debug] 			Position:		" + String(control.manipulatorOpenClose) + "\n"\ //code for official manipulator
		// 					"								Rotation:		" + String(control.manipulatorRotation));
	}
	if(bitRead(debug_mode, debug_type_bits::networking)==1)//Networking debug
	{
		SerialUSB.println("[Networking debug]");
		Networking::status();
	}
	if(bitRead(debug_mode, debug_type_bits::thrusters)==1)//Thrusters debug
	{
		SerialUSB.println("[Thrusters debug]"); 
		SerialUSB.println(Thrusters::status);
	}
	if(bitRead(debug_mode, debug_type_bits::reset)==1)//Reset debug
	{
		debug_mode = 0b00000000;
	}

}

void HighROV::run() {
		using namespace config;
		using namespace pwm;
		serialHandler();
		AnalogSensors::update();
		if (!standalone || force_ethernet_init) {
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

		manip_pos += control.manipulatorOpenClose*manip_speed/100;
		manip_pos = constrain(manip_pos, -100,100);

		PWMController::set_thruster(7, manip_pos);

		if (DepthSensor::getUpdateStatus() == true) {
			analogWrite(LED_BUILTIN, sin(millis() * 0.01) * 127 + 127);
		} else {
			analogWrite(LED_BUILTIN, 255);
		}

		debugHandler();

}

