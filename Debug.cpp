#include "Debug.h"
#include "Config.h"
#include "Data.h"
#include "api/Common.h"
using namespace config::debug;

String a;


long long last_output = 0;
static const String ayana[] = {
"	oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo++oooooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo:. +ooooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo:..~..ooooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooo+:++oooooooooooooooooooooooooo:...+~ .:oooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooo+. .:~~~~~:~::+++++:::~::::::....~o+~.~oooooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooo+..~++:...        .   .      .~.+oo+.~oooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooo:. ~oo+:.~.      ..... ..    ..+oo+..oooooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooooo~. +ooo:.. ........... ......:o+o: ~oooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooooo~ +oo+:.....~..~...~.~~.~~..:+oo~ :oooooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooooooo:.:+~...~~~.~~..~~~~..~~~.. ~++...oooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooooooo+~~~ .....~.:~~~~~...~... . ...  +ooooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooooooooo+~..  . .....~~.~.. ........  ..~ooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooooooo+~~:.... .....~.....~:+++:~..   ..ooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooooooo:.:~.~.~.....~~~~~.~+~.~......    +oooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooooooooooooooooooooo...~..~+~~~:~:~~~~~oo+  ~.~....   +oooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooooooo+ ......~~.~~:~~~:~:++++.~~~...    .oooooooooooooooooooo\n\r",
"	oooooooooooooooooooooooooooooooooooooooooooo~  ...~:+. ~+++++++.   ..~~.. .     +ooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooooo+:..  ...+o+++ooooooo+:::+~~~. ..     :ooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooooo:...   ..~++++o+ooo+o+++++~~~. .   .   ooooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooooo+~.....~. ..+ooooo+oooo+o+++~~. .    .  ::oooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooooo++++++++oo+:..~++ooo+++ooooo+:~..     ... o:+ooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooooooo+:++oo+oooo++o+.~::++++oo++:~~:..   . . ..:.+o~ooooooooooooooooo\n\r\
	oooooooooooooooooooooooooooooooo++.~:oo+o+++++++++:~..           .~~. ........:+~o+:oooooooooooooooo\n\r\
	ooooooooooooooooooooooooooo+++:..~:+ooo+++++++++++~. .   ~+~.~::: ~+:::~.  ...~o:+o~:ooooooooooooooo\n\r\
	ooooooooooooooooooooooo+::.....:++oooo++++++ooo+o+~~.. .~++++++~  ++ooo+. .....+++oo :oooooooooooooo\n\r\
	ooooooooooooooooooo+:.     . .+oooo++++:++o++oo+:. ..~:.:++:~....:o:+++o+... ..:o:oo+ :ooooooooooooo\n\r\
	ooooooooooooooo+:.  .~:+~..:++ooooooo++++o++::~.~.~:+~.~~~:..~...~++++++o+.. . .++:oo+ ~oooooooooooo\n\r\
	oooooooooooo+:  .:++oo+~:+oo+++oo++o+o++::...~++o+~++:~:~~~~~:~.:+++o++oo+~. ~: ~o~+oo+ .+oooooooooo\n\r\
	o+oooooooo+:  .+oooo+~~ooo++++++o+++++~ . .:+oooo+:+:~::++++:.~+o++++++o++....o+.~+.ooo+::+ooooooooo\n\r\
	o++oooooo+.  ~+oooo+.+o+::::~~~:~~:+o~ .~~o+o++o++:::+~:+:~~.~ooo++:+o++++: . +oo:~ :ooo+o+++ooooooo\n\r\
	oo+:+ooo+. .~+oo++:..~.~~~..     .~:++.+:o+++++o+++:++::~...~oo+oo++++++++~ . ~oooo..+ooooo+++++oooo\n\r\
	oooo+~::...:~+~.       .~.  .....    ~:o++++++++++:+++++....+ooo++:+o+++o:  .. +ooo~ :::+ooooo+~~++o\n\r\
	oooooo+~..+:~    ..          ...      .~~:+++++++++++++::. ~++++++:++oo++ ..  ..:oo: :++~.~++o::o+.~\n\r",
"	ooooooo+~~o:~ .......     ...~...        ~:::+++++++++:+:  .+++++:+++++++~....~. .+~ ~ooo+~ .~.+oo+.\n\r\
	oooooooo++o:. .........   ..~....     ..  .++++++++++++++. ~~++::+o+o++++:~...o+......:++++.  +oooo+\n\r\
	oooooooo++: ..  .... ...  .... ..      .. ..:+++++++++++++::+:+::+o++ooo+::~. ~oo:.... .:+++~.+ooooo\n\r\
	oooooooo+. .   .......   ..~~....      ......~++++++++++++++++:+++o++o+o+:::.  +oo~ .....~:o+:oooooo\n\r\
	ooooooo+  .  .:  ... ... .....~.         . .. .:+++oo+++++:::::oo+oooo++:::::~ .+o. ...~.  ..+oooooo\n\r\
	oooooo+~ . .+oo~ ....... ......       . ..~...  ~ooo+o++++.~+:+oo++++:~~~~::~+. .:   +: ~. . .~+oooo\n\r\
	oooooo+~  ~oooo+ ......  .......        ........ .++o+o+++~.::+oo+~:~:~.~:~~~:+. .   oo+... . +~:+oo\n\r\
	ooooooo. :oooooo: .. ..  ~.~... .       ........~  ~++++o+~ :+:oo+::~:~~~:~~~~+:   .:~+o+~. . :o++++\n\r\
	oooo+oo::ooooooo+   .    ..... .         ... . ...  .+++++~ ~+++oo:~~~~.+~~~~.:+ ...~.~~:~.....ooooo\n\r\
	ooo+:ooooooooo+..~  ..   .....          .......~...   :+o++:++++oo:~~~~ +~~~~~:~   .. ::::~~.. +oooo\n\r\
	oooo+:++++++~~~++o+      ...              ...~.... .  ~.+oo++++:oo+~~~..+~.~~. .. ...  ~:+~:.. +oooo\n\r\
	oooooo++++++ooooooo.    ....              . ..... ..  .~ :+o++:+oo+~~~..o.~~...~... .. ~:.~:~. ooooo\n\r\
	oooooooooooooooooooo.    .                  .......    ~. .+o+++ooo..~ :o.....::~...~. ~o+~~~ :ooooo\n\r\
	oooooooooooooooooooo+                      ....... .  .~.~ .+++++oo~...o+ .~.:o+:~.~~   o++~..oooooo\n\r\
	ooooooooooooooooooooo~                       ...  ... ~~~.  ~o++ooo~..:o~...~+o+:~~~.   o++:. oooooo\n\r\
	ooooooooooooooooooooo+                            .   .~. .  :+ooo+...o:.. ~+o+:++:~~  :o:+: ~+ooooo\n\r",
"	ooooooooooooooooooooo:                                 ...~ .+oooo+..+:~~.~oo++++::+~  ++++::~+ooooo\n\r\
	oooooooooooooooooooo+                                  :~..:oooooo~.+~+:~+oooooooo.~  +oooo++:+ooooo\n\r\
	ooooooooooooooooooo~.         ..                       .. .oooooo+~oo+oooooooooo+.   +oooooooooooooo\n\r\
	oooooooooooooooooo~             :~::++:~::~.  ..      .~   .oooo+:oooooooooooo+~    +ooooooooooooooo\n\r\
	ooooooooooooooooo~              ~oooooooooo++++++++:++oo.   .+oooooooooooooo+~    ~ooooooooooooooooo\n\r\
	oooooooooooooooo:     ~          +ooooooooooooooooooooooo.    ~+ooooooo++~..    ~+oooooooooooooooooo\n\r\
	ooooooooooooooo+ .   ..          .oooooooooooooooooooooooo+.     ....        ~+ooooooooooooooooooooo\n\r\
	oooooooooooooo+. .                +ooooooooooooooooooooooooo+~.         .~:+oooooooooooooooooooooooo\n\r\
	oooooooooooo+~ ... .   . .        ooooooooooooooooooooooooooooo++++++++ooooooooooooooooooooooooooooo\n\r\
	ooooooooooo+..... .   ~o+        ~oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\r\
	ooooooooooo~ .... ..  +oo.   ..   oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\r\
	ooooooooooo+~       ~+ooo. ..     +ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\r\
	ooooooooooooo+::::++ooooo~. .     ~ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooo~ ..     ~ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooo+.      ~oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\r\
	ooooooooooooooooooooooooooo+~.~~+ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\r"
};
int i = 0;
void Debug::debugHandler(rov::RovControl control){
	using namespace config::debug;
	if (millis() > (output_interval + last_output)) {
		if(BIT_CHECK(debug_mode, debug_type_bits::analog_sensors)==1)//analog sensors debug
		{
			SerialUSB.println("[analog sensors debug]		Amperage:		" + String(AnalogSensors::getAmperage()) + "\n\r"\
								"							Voltage: 		" + String(AnalogSensors::getVoltage()));
		}
		if(BIT_CHECK(debug_mode, debug_type_bits::depth_sensor)==1)//depth sensor debug
		{
			if(!standalone || force_depth_sensor_init){
				SerialUSB.println("[depth sensor debug] 		Depth:			" + String(DepthSensor::getDepth()) + "\n\r");
			}
			else {
				SerialUSB.println("Depth sensor support disabled, turning off debug mode 0b00000010\n");
				BIT_CLEAR(debug_mode, debug_type_bits::depth_sensor);
			}
		}
		if(BIT_CHECK(debug_mode, debug_type_bits::imu)==1)//IMU debug
		{
			SerialUSB.println("[IMU debug] 				Yaw/Roll/Pitch:	" + String(IMUSensor::getYaw(), 2) + "/" + String(IMUSensor::getRoll(),2) + "/" + String(IMUSensor::getPitch()));
		}
		if(BIT_CHECK(debug_mode, debug_type_bits::manipulator)==1)//Manipulator debug
		{
			SerialUSB.println("[Manipulator debug] 			Position:		" + String(control.manipulatorOpenClose) + "\n\r" //code for official manipulator
							  "								Rotation:		" + String(control.manipulatorRotation));
		}
		if(BIT_CHECK(debug_mode, debug_type_bits::networking)==1)//Networking debug
		{
			if(!standalone || force_ethernet_init){
				SerialUSB.println("[Networking debug]");
				Networking::status();
			}
			else {
				SerialUSB.println("Ethernet support disabled, turning off debug mode 0b00001000");
				BIT_CLEAR(debug_mode, debug_type_bits::networking);
			}
		}
		if(BIT_CHECK(debug_mode, debug_type_bits::thrusters)==1)//Thrusters debug
		{
			SerialUSB.println("[Thrusters debug]"); 
			SerialUSB.println(Thrusters::status);
		}
		if(BIT_CHECK(debug_mode, debug_type_bits::reset)==1)//Reset debug
		{
			// debug_mode = 0b00000000;
		}
		last_output = millis();
	}
}

void Debug::debugMenu(){
	SerialUSB.print("Debug menu:\n\r"\
					"1 - analog sensors\n\r"\
					"2 - depth sensor\n\r"\
					"3 - IMU\n\r"\
					"4 - manipulator\n\r"\
					"5 - networking\n\r"\
					"6 - thrusters\n\r"\
					"7 - reset\n\r"\
					"8 - neko\n\r"\
					"0 - exit\n\r"\
					"Currently flags are: 0x");
	SerialUSB.println(debug_mode, BIN);
	SerialUSB.print("Your choice: ");
	while (!SerialUSB.available());

	String msg = SerialUSB.readString();
	msg.trim();
	SerialUSB.println(msg);
	int debug_curr = msg.toInt();

	if(debug_curr==8){
		SerialUSB.println("Hi, I'm your ROV's neko girl, Ayana, and I am responsible for debugging all of this, nya!\n\r");
		for(int i = 0; i<4; i++){
			SerialUSB.print(ayana[i]);
		}
		return;
	}
	if(debug_curr < 0 || debug_curr > 7){
		SerialUSB.println("wrong input, please resend the input one number at a time");
	}
	if (debug_curr == 2 && (standalone && !force_depth_sensor_init)) {
		SerialUSB.println("Depth sensor is disabled, please change config variables 'bool standalone' and 'bool force_depth_sensor_init', turning depth sensor debug off");
	}
	if (debug_curr == 5 && (standalone && !force_ethernet_init)) {
		SerialUSB.println("Ethernet communication is disabled, please change config variables 'bool standalone' and 'bool force_ethernet_init', turning ethernet debug off");
	}

	if(!(debug_curr<=0 || debug_curr>7) && ((debug_curr == 2 && (!standalone || force_depth_sensor_init)) || (debug_curr == 5 && (!standalone || !force_ethernet_init))))
		BIT_FLIP(debug_mode, debug_curr-1);
	
	SerialUSB.print("Exit the debug menu? [y/n]");

	while (!SerialUSB.available());
	msg = SerialUSB.readString();
	msg.trim();
	SerialUSB.println(msg);
	msg.toLowerCase();
	if (msg == "n") {
		SerialUSB.println("Returning to debug menu...");
		debugMenu();
	}
	else {
		if (msg == "y") {
			SerialUSB.println("Resuming firmware execution");
		}
		else {
			SerialUSB.println("Assuming y, resuming firmware execution");
		}
	}



}
