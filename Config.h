#pragma once
#include <stdint.h>
#include "variant.h"

#define ISERIAL_MAX_LEN         1024
namespace config {
    /* pinout */
    namespace pwm {
        /* thrusters */
        constexpr int th_horizontal_front_left_pin  = 2;
        constexpr int th_horizontal_front_right_pin = 3;
        constexpr int th_horizontal_back_left_pin   = 4;
        constexpr int th_horizontal_back_right_pin  = 5;
        constexpr int th_vertical_front_pin         = 6;
        constexpr int th_vertical_back_pin          = 7;
        /* additional custom thrusters */
        constexpr int th_custom_0_pin   = 8;
        constexpr int th_custom_1_pin   = 9;

        /* cam servos pins */
        constexpr int servo_front_pin   = A4;
        constexpr int servo_back_pin    = A5;

        /* video multiplexer */
        constexpr int cam_select_pin    = 10;

        /* custom PWM pins */
        constexpr int pwm_custom_a2_pin = A2;
        constexpr int pwm_custom_a3_pin = A3;

        /* manipulator PCA9536 channels */
        constexpr int manip_grab_ch     = 0;
        constexpr int manip_release_ch   = 1;

        constexpr int manip_left_ch     = 2;
        constexpr int manip_right_ch    = 3;
    }

    /* indices of thrusters (controlled by SAMD_ISR_SERVO) */
    namespace thrusters {
        enum thrusters {
            horizontal_front_left = 0,
            horizontal_front_right,
            horizontal_back_left,
            horizontal_back_right,
            vertical_front_left,
            vertical_front_right,
            vertical_back_left,
            vertical_back_right,
            custom_0,
            custom_1,
        };
    }

    /* indices of servos (controlled by Servo.h) */
    namespace servos {
        enum servos {
            front = 0,
            back,
            pwm_a2,
            pwm_a3,
        };
    }

    namespace networking {
        constexpr uint8_t selfip[4] = {192, 168, 1, 5};
        constexpr uint16_t self_port = 3020;
        constexpr uint8_t remoteip[4] = {192, 168, 1, 4};
        constexpr uint16_t remote_port = 3010;
        constexpr uint8_t cs_pin = 43; // W5500 CS on PA13 pin
    }

    namespace analog {
        constexpr int ammeter_pin = A0;
        constexpr int voltmeter_pin = A1;

        constexpr double voltage_multiplier  = 0.016064;
        constexpr double amperage_multiplier = 0.077821;
        constexpr double amperage_deflection = 512.0;
    } // namespace analog

    namespace debug {
        uint8_t debug_mode = 0;
        constexpr bool standalone = 0;					//Turns off most of the external devices, allowing "clean" initialisation without any connections 
        constexpr bool force_ethernet_init = 0;		    //Forcibly turns on the Ethernet controller present on the board. WARNING, the board can hang when initialising Ethernet controller without proper connection to external Ethernet device
        constexpr bool force_depth_sensor_init = 0;   	//Forcibly turns on the depth sensor. for it to work, you need to connect the secondary board with depth sensor present
        constexpr int output_interval = 300;
        enum debug_type_bits{
            analog_sensors = 0,
            depth_sensor,
            imu,
            manipulator,
            networking,
            thrusters,
            reset
        };
    }
}
