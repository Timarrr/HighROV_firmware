#include "DepthSensor.h"
#include "HighROV.h"
#include "Config.h"
#include "AnalogSensors.h"
#include "IMUSensor.h"
#include "Networking.h"
#include "Thrusters.h"
#include "USB/USBAPI.h"
class Debug {
	public:
		static void debugHandler();
		static void debugMenu();
};
