#include "Debug.h"
#include "Config.h"
using namespace config::debug;

String a;

long long last_output = 0;
static const String ayana[] = {
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
int i = 0;
void Debug::debugHandler(){
	using namespace config::debug;
	if (millis() > output_interval + last_output) {
		if(bitRead(debug_mode, debug_type_bits::analog_sensors)==1)//analog sensors debug
		{
			SerialUSB.println("[analog sensors debug]		Amperage:		" + String(AnalogSensors::getAmperage()) + "\n"\
								"							Voltage: 		" + String(AnalogSensors::getVoltage()));
		}
		if(bitRead(debug_mode, debug_type_bits::depth_sensor)==1)//depth sensor debug
		{
			if(!standalone || force_depth_sensor_init){
				SerialUSB.println("[depth sensor debug] 		Depth:			" + String(DepthSensor::getDepth()) + "\n");
			}
			else {
				SerialUSB.println("Depth sensor support disabled, turning off debug mode 0b00000010");
				bitClear(debug_mode, debug_type_bits::depth_sensor);
			}
		}
		if(bitRead(debug_mode, debug_type_bits::imu)==1)//IMU debug
		{
			SerialUSB.println("[IMU debug] 				Yaw/Roll/Pitch:	" + String(IMUSensor::getYaw(), 2) + "/" + String(IMUSensor::getRoll(),2) + "/" + String(IMUSensor::getPitch()));
		}
		if(bitRead(debug_mode, debug_type_bits::manipulator)==1)//Manipulator debug
		{
			SerialUSB.println("[Manipulator debug] 		Position:		" + String(HighROV::manip_pos));
			// SerialUSB.println("[Manipulator debug] 			Position:		" + String(control.manipulatorOpenClose) + "\n"\ //code for official manipulator
			// 					"								Rotation:		" + String(control.manipulatorRotation));
		}
		if(bitRead(debug_mode, debug_type_bits::networking)==1)//Networking debug
		{
			if(!standalone || force_ethernet_init){
				SerialUSB.println("[Networking debug]");
				Networking::status();
			}
			else {
				SerialUSB.println("Ethernet support disabled, turning off debug mode 0b00001000");
				bitClear(debug_mode, debug_type_bits::networking);
			}
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
		last_output = millis();
	}
}

void Debug::debugMenu(){
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
		bitToggle(debug_mode, debug_curr-1);
	
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
