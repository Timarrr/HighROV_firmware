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

String ayana[] = {
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠙⠻⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⡞⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠀⡀⠀⠀⠀⠈⠉⠉⠉⠛⠛⠿⠿⠿⠛⠛⠋⠉⠉⠉⠉⠛⠛⠛⠃⠀⠀⠀⠀⢸⣷⣀⡀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⠀⠑⢮⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⠁⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠈⢿⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⠃⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⢸⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢼⣿⣿⣿⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠸⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠪⣿⣿⣇⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠈⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⡻⠇⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠐⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠶⠟⠒⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠚⠛⠿⢿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⡀⣰⠀⠀⢠⣤⣷⣤⣄⣰⣶⣶⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⢹⣿⣄⢶⣤⣿⣿⣿⣿⣿⣿⣿⢀⣄⡀⢹⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣿⣵⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⡿⢃⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⢀⣤⣄⣴⣶⣾⣿⣿⣷⣄⠀⠀⠀⠙⠿⣿⣿⣿⣤⣀⣠⣿⣿⣿⣿⡾⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣇⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢋⣴⢠⣿⣿⢿⣿⣿⣿⣿⣿⠈⣹⡗⠀⠀⠀⠀⠈⠙⠻⠿⣿⣿⠿⠟⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡆⠀⣿⡄⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⢀⣤⣿⣿⠘⣿⣿⣯⡃⠻⠹⠃⠷⢾⡯⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⠀⢿⣷⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⢀⣤⣾⣿⣿⣿⣷⣮⠍⠉⠉⣀⣤⣴⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠤⠀⠀⠀⢠⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⢸⣿⣇⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠋⠁⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⡿⠿⠉⠀⠀⣸⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⢀⠃⠈⠁⢸⠟⠊⠀⠀⢠⣾⢋⣽⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⣿⡀⣿⣿⡄⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣷⡆⢠⢰⣾⣿⣿⢻⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠨⣍⠢⠒⠀⠀⠀⠀⠀⢸⡿⠸⢫⡿⣿⣷⡀⠀⠀⠀⠀⠀⠀⢻⣇⢹⣿⣷⡀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠉⠀⠀⠀⢀⣀⣤⡴⠂⠀⣀⣤⡆⣼⣿⣿⣿⣿⣿⣿⣿⡇⣾⢿⣿⡿⠡⠞⠛⠉⠀⢀⡀⠀⠈⠑⠀⠀⠀⡀⠀⠁⠀⠀⠀⠀⠀⠀⢀⢷⣦⠸⠃⡟⣿⡏⠁⠀⠀⠀⠀⠀⠸⣿⡀⢿⣿⣧⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⠀⠀⢀⣤⣶⣿⣿⡿⠋⢀⣴⣾⣿⣿⢀⢿⣿⣿⣿⣿⣿⣿⣿⣵⠏⠀⠉⠀⠀⠀⣠⣴⣾⣿⡇⠀⠘⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⢠⡿⣷⣤⢸⣿⡇⡃⠀⠀⠀⢆⠀⠀⢻⣇⠘⣿⣿⣧⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⠁⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⢀⣾⣿⣿⣿⣿⠋⢀⣴⣿⣿⠟⠋⠀⠀⠉⠙⠛⠿⠟⠛⠛⣉⠅⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⠇⠐⠀⠆⠀⠀⢀⠘⠴⠆⠸⠀⠀⢀⣾⣿⣿⠀⡧⣼⣿⣻⣿⣾⠃⠀⠀⠀⢸⣷⡀⠀⢻⠀⢻⣿⣿⣦⠱⣄⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣆⢻⣿⣿⣿⣿⣿⣿⠋⠀⠀⠀⢀⣾⣿⣿⣿⡿⠁⠀⡾⠛⠋⠀⠀⠀⠀⠀⠀⠚⠋⠁⢀⣴⣿⡏⠀⠀⡀⢀⣾⢸⣿⣿⣿⣿⣏⠀⠐⠀⢀⡬⠀⠀⢸⠀⠀⠀⠀⢠⣿⣿⣿⣿⠀⡁⢿⣿⣿⣿⠟⠀⠀⠀⠀⠀⣿⣿⣦⡀⠁⠈⣿⣿⣿⣷⣝⢷⣄⡙⢿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣦⠙⠻⣿⣿⣿⠁⠀⠀⠀⠀⣼⣿⡿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⢰⠀⣼⠁⣾⠟⠈⣿⣿⣿⣿⡿⠀⠠⠂⣴⠀⡄⠂⠈⠀⠀⠀⢠⣿⣿⣿⣿⣿⠀⢬⣶⣤⣤⣶⣆⡀⠀⠀⠀⠀⢻⣿⣿⣿⡆⠀⢹⣿⣿⣿⣿⣷⣮⣙⠲⠍⠻⣿⣿⣿⣿\n\
	⣿⣿⣿⣷⣄⡀⠉⠃⠀⠀⠠⠀⠀⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⣿⡠⠋⣴⡧⢘⠿⠿⠋⠁⠀⠀⣸⡏⠰⠰⠈⠀⠀⠀⠀⣾⣿⣿⣿⣿⠟⠀⢸⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠘⣿⣿⣿⡇⠀⠀⡉⠙⠻⢿⣿⣿⣿⣿⣶⡄⠀⠙⢿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣶⠀⠀⠀⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠃⠐⠁⠀⠀⠁⠀⠀⠀⠀⠀⠿⠁⠄⠀⠀⠀⠀⠀⢠⡿⠿⠟⠋⠁⠀⢀⢸⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠈⢿⣿⡇⠀⠀⣿⣦⣀⠀⠈⠙⢿⣿⠇⠀⣿⣆⠀⠙\n\
	⣿⣿⣿⣿⣿⣿⣧⣦⠀⢰⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⢀⠀⣶⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⢀⠀⠀⠀⠉⠃⠀⠀⣿⣿⣿⣷⡀⠀⠀⠉⠀⣼⣿⣿⣧⠀\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⡆⣾⣿⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡾⣠⣀⣀⣾⡦⢀⠙⠀⠀⠠⣀⣧⠀⠀⢀⠘⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠘⣷⡀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠛⠂⠀⠀⠘⣿⣿⣿⣿⣧\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⡇⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢛⣻⣯⣅⣤⣜⣁⣀⠒⠾⢮⣿⣷⣄⠘⠃⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⢻⣿⣦⡀⠀⠀⠀⠀⠀⠲⢶⣶⣶⡄⠀⡇⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⡿⠩⡿⣉⡛⠛⠿⣷⣄⡀⠁⠀⠀⠀⠀⠀⣰⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠙⠻⡇⢠⣧⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⢀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⣶⣠⣾⣿⣿⣷⣬⣙⠛⠤⠀⠀⠀⠀⠸⣿⡏⢿⣿⣿⣿⣿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠹⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠺⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⢀⣴⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⢰⣿⣿⠘⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⢆⠀⠀⠉⠀⠀⠀⢠⣆⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⢰⠀⠀⠀⣠⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣷⡉⠻⠀⠀⠀⠀⢸⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⠀⠀⠀⠀⠀⢸⣿⣧⠀⠀⠀⠀⠀⠀⢰⣄⠈⠻⣿⣿\n",
"	⣿⣿⣿⣿⣿⣇⣾⠀⠀⢰⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠊⠝⠻⣿⣿⣦⠀⠀⠀⠀⠘⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠈⠻⠿⣧⠀⠀⠀⠀⠀⠈⣿⣿⣦⣌⡛\n\
	⣿⣿⣿⡏⢿⣿⣿⡄⣦⣻⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⣠⣈⠙⢬⠀⠀⠀⠀⠀⣿⣿⣷⠀⠀⠀⠀⠀⢰⠀⠀⠀⠀⠀⠀⣴⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣇⠸⣿⣿⣇⣿⣿⣿⣿⣿⡿⠛⠁⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣦⡉⠲⢄⠀⠀⢸⣿⣿⠀⠀⠀⠀⠀⢸⡄⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠢⡀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣆⡈⠻⢿⣿⡿⠟⠋⠁⢀⣠⣴⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣦⠀⠁⠀⠸⣿⣿⡄⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣾⣿⣶⡀⠀⠀⣿⣿⡇⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣷⠀⢸⣿⣿⡇⠀⠀⠀⠀⣸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⢣⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⡇⠜⣿⣿⡇⠀⠀⠀⢠⣿⠁⠀⠀⠀⠀⣾⣦⠀⠀⠀⠀⠀⠀⠀⠀⢹⡇⣶⠀⠀⠀⣼⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡧⣾⣿⣿⡇⠀⠀⠀⣼⡟⠀⠀⠀⠀⣰⣿⡟⠐⠀⠀⠀⠀⠀⠀⠀⣿⡇⣿⠀⠀⠀⢻⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢡⣧⣿⣿⣿⡇⠀⠀⢰⡿⠀⠀⠀⠀⣠⣿⡿⠃⠐⠁⠀⠀⠀⠀⠀⠀⣿⠁⠃⠀⠀⠀⠸⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣯⣾⣿⣿⣿⠃⠀⠀⡾⠁⡔⠀⢀⣴⣿⣯⣀⣀⣀⣀⠀⠀⠀⠀⠀⣸⣇⠀⠀⠁⠀⠀⠀⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⡿⠀⢰⠆⣠⠞⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⠆⠀⠀⠀⢠⣿⣿⣿⣿⣶⣀⠀⢀⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⠇⣠⣷⣦⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣀⣀⣀⣠⣤⣄⣀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠹⣿⣿⣿⣿⢏⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣤⣤⣤⣤⣤⣤⣀⣤⣾⣿⣷⡀⠀⠀⠀⠘⢿⣿⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠉⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣦⣤⣤⣤⣤⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣄⣀⣀⣠⣴⣾⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",
"	⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⣀⣀⣀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
};
rov::RovControl control;
rov::RovTelemetry Telemetry;
int manip_speed = 100;
int manip_pos = -20;
uint8_t debug_type = 0b00000000;


void HighROV::init() {
		SerialUSB.println("HighROV init!");

		pinMode(LED_BUILTIN, OUTPUT);
		analogWrite(LED_BUILTIN, 100);

		PWMController::init();
		Networking::init();
		Thrusters::init();
		RotaryCameras::init();
		DepthSensor::init();
		Manipulator::init();
		IMUSensor::init();
		AnalogSensors::init();

	delay(3000);
}

void debug(rov::RovControl &ctrl) {
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
	SerialUSB.println(debug_type, BIN);
	SerialUSB.print("Your choice: ");
	while (!SerialUSB.available());

	String msg = SerialUSB.readString();
	msg.trim();
	SerialUSB.println(msg);
	int debug_curr = msg.toInt();
	if(debug_curr==8){ // nya.jpg
		SerialUSB.println("Hi, I'm your ROV's neko girl, Ayana, and I am responsible for debugging all of this, nya!\n");
		for(int i = 0; i<33; i++){
			Serial.println(ayana[i]);
			delay(15);
		}
	}
	if(debug_curr<=0 || debug_curr>7){
		SerialUSB.println("wrong input, please resend the input one number at a time");
		return;
	}
	bitToggle(debug_type, debug_curr);
	SerialUSB.println(debug_type);
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
	if(bitRead(debug_type, 0)==1)//analog sensors debug
		{
			SerialUSB.println("[analog sensors debug]		Amperage:		" + String(AnalogSensors::getAmperage()) + "\n"\
							 	 "                     			Voltage: 		" + String(AnalogSensors::getVoltage()));
		}
		if(bitRead(debug_type, 1)==1)//depth sensor debug
		{
			SerialUSB.println("[depth sensor debug] 			Depth:			" + String(AnalogSensors::getAmperage()) + "\n");
		}
		if(bitRead(debug_type, 2)==1)//IMU debug
		{
			SerialUSB.println("[IMU debug] 					Yaw/Roll/Pitch:	" + String(IMUSensor::getYaw(), 2) + "/" + String(IMUSensor::getRoll(),2) + "/" + String(IMUSensor::getPitch()));
		}
		if(bitRead(debug_type, 3)==1)//Manipulator debug
		{
			SerialUSB.println("[Manipulator debug] 			Position:		" + String(control.manipulatorOpenClose) + "\n"\
								 "								Rotation:		" + String(control.manipulatorRotation));
		}
		if(bitRead(debug_type, 4)==1)//Networking debug
		{
			SerialUSB.println("[Networking debug]			");
			Networking::status();
		}
		if(bitRead(debug_type, 5)==1)//Networking debug
		{
			SerialUSB.println("[Thrusters debug]				" + Thrusters::status);
		}
		if(bitRead(debug_type, 6)==1)//Reset debug
		{
			debug_type = 0b00000000;
		}

}

void HighROV::run() {
		using namespace config;
		using namespace pwm;
		serialHandler();
		AnalogSensors::update();
		Networking::maintain();

		Telemetry.yaw = IMUSensor::getYaw();
		Telemetry.roll = IMUSensor::getRoll();
		Telemetry.pitch = IMUSensor::getPitch();
		Telemetry.depth = DepthSensor::getDepth();
		Telemetry.temperature = DepthSensor::getTemp();
		Telemetry.ammeter = AnalogSensors::getAmperage();
		Telemetry.voltmeter = AnalogSensors::getVoltage();
		Telemetry.cameraIndex = RotaryCameras::get_cam_index();


		Networking::read_write_udp(Telemetry, control);
		if (!control.debugFlag) {
			Thrusters::update_thrusters(control, Telemetry);

			RotaryCameras::set_angle(config::servos::front, constrain(control.cameraRotation[0], -1, 1) * 3.0);
			RotaryCameras::set_angle(config::servos::back,  constrain(control.cameraRotation[1], -1, 1) * 3.0);
			RotaryCameras::select_cam(control.cameraIndex == 1 ? true : false);

			manip_pos += control.manipulatorOpenClose*(manip_speed/20);
			manip_pos = constrain(manip_pos, -100,100);
							
			PWMController::set_thruster(7, manip_pos);
		} else {
			debug(control);
		}

		if (DepthSensor::getUpdateStatus() == true) {
			analogWrite(LED_BUILTIN, sin(millis() * 0.01) * 127 + 127);
		} else {
			analogWrite(LED_BUILTIN, 255);
		}

		debugHandler();

}

