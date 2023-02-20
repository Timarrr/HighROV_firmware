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
	PWMController::set_thruster(vertical_front_left, 0);
	PWMController::set_thruster(vertical_back_left, 0);
	PWMController::set_thruster(custom_0, 0);
	PWMController::set_thruster(custom_1, 0);
}

void Thrusters::update_thrusters(rov::RovControl &ctrl, rov::RovTelemetry & tel) {
	using namespace config::thrusters;
	auto &data = inst();

	PWMController::set_thruster(thrusters::horizontal_front_left,  ctrl.thrusterPower[0]);
	PWMController::set_thruster(thrusters::horizontal_front_right, ctrl.thrusterPower[1]);
	PWMController::set_thruster(thrusters::horizontal_back_left,   ctrl.thrusterPower[2]);
	PWMController::set_thruster(thrusters::horizontal_back_right,  ctrl.thrusterPower[3]);
	PWMController::set_thruster(thrusters::vertical_front_left,    ctrl.thrusterPower[4]);
	PWMController::set_thruster(thrusters::vertical_front_right,   ctrl.thrusterPower[5]);
	PWMController::set_thruster(thrusters::vertical_back_left,     ctrl.thrusterPower[6]);
	PWMController::set_thruster(thrusters::vertical_back_right,    ctrl.thrusterPower[7]);
	
	status = (
		"0-HFL:	" + (String) ctrl.thrusterPower[0] + "	1-HFR:	" + (String) ctrl.thrusterPower[1] + "\n\r"
		"2-HRL:	" + (String) ctrl.thrusterPower[2] + "	3-HRR:	" + (String) ctrl.thrusterPower[3] + "\n\r"
		"4-VFL:	" + (String) ctrl.thrusterPower[4] + "	5-VFR:	" + (String) ctrl.thrusterPower[5] + "\n\r"
		"6-VRL:	" + (String) ctrl.thrusterPower[6] + "	7-VRR:	" + (String) ctrl.thrusterPower[7] + "\n\r"
	);

}

Thrusters & Thrusters::inst() {
	static Thrusters th;
	return th;
}
