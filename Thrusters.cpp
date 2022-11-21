#include "Thrusters.h"
#include "PWMController.h"
#include "Config.h"

String Thrusters::status = "";

void Thrusters::init() {
	using namespace config::thrusters;
	SerialUSB.println("Thrusters init");
	PWMController::set_thruster(horizontal_front_left, 0);
	PWMController::set_thruster(horizontal_front_right, 0);
	PWMController::set_thruster(horizontal_back_left, 0);
	PWMController::set_thruster(horizontal_back_right, 0);
	PWMController::set_thruster(vertical_front, 0);
	PWMController::set_thruster(vertical_back, 0);
	PWMController::set_thruster(custom_0, 0);
	PWMController::set_thruster(custom_1, 0);
}

void Thrusters::update_thrusters(rov::RovControl &ctrl, rov::RovTelemetry & tel) {
	using namespace config::thrusters;
	auto &data = inst();

	{
		// deprecated
		// const int16_t y = ctrl.axisY;
		// const int16_t x = ctrl.axisX;
		// const int16_t w = ctrl.axisW;
		// const int16_t z = ctrl.axisZ;

		// PWMController::set_thruster(horizontal_front_left,  constrain(data.directions[0] * (y + x + w), -100, 100));
		// PWMController::set_thruster(horizontal_front_right, constrain(data.directions[1] * (y - x - w), -100, 100));
		// PWMController::set_thruster(horizontal_back_left,   constrain(data.directions[2] * (y - x + w), -100, 100));
		// PWMController::set_thruster(horizontal_back_right,  constrain(data.directions[3] * (y + x - w), -100, 100));

		// PWMController::set_thruster(vertical_front, constrain(data.directions[4] * z, -100, 100));
		// PWMController::set_thruster(vertical_back,  constrain(data.directions[5] * z, -100, 100));

		PWMController::set_thruster(thrusters::horizontal_front_left,  ctrl.thrusterPower[0]);
		PWMController::set_thruster(thrusters::horizontal_front_right, ctrl.thrusterPower[1]);
		PWMController::set_thruster(thrusters::horizontal_back_left,   ctrl.thrusterPower[2]);
		PWMController::set_thruster(thrusters::horizontal_back_right,  ctrl.thrusterPower[3]);
		PWMController::set_thruster(thrusters::vertical_front,         ctrl.thrusterPower[4]);
		PWMController::set_thruster(thrusters::vertical_back,          ctrl.thrusterPower[5]);
		
		status = ("Thruster HorFrontLeft:	" + (String) ctrl.thrusterPower[0] + "	Thruster HorFrontRight	" + (String) ctrl.thrusterPower[1] +\
		   "\n" + "Thruster HorBackLeft:	" + (String) ctrl.thrusterPower[2] + "	Thruster HorBackRight	" + (String) ctrl.thrusterPower[3] +\
		   "\n" + "Thruster VerFront :		" + (String) ctrl.thrusterPower[4] + "	Thruster VerBack		" + (String) ctrl.thrusterPower[5]);
	}
}

Thrusters & Thrusters::inst() {
	static Thrusters th;
	return th;
}
