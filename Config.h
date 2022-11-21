#pragma once
#include <stdint.h>
#include "variant.h"

#define ISERIAL_MAX_LEN         1024
#ifndef CONFIG_H
#define CONFIG_H
namespace config {
    /* pinout */
    namespace pwm {
        /* thrusters */
//        constexpr int th_horizontal_front_left_pin  = 2;
//        constexpr int th_horizontal_front_right_pin = 3;
//        constexpr int th_horizontal_back_left_pin   = 4;
//        constexpr int th_horizontal_back_right_pin  = 5;
//        constexpr int th_vertical_front_pin         = 6;
//        constexpr int th_vertical_back_pin          = 7;

        constexpr int th_horizontal_front_left_pin  = 6; //6
        constexpr int th_horizontal_front_right_pin = 7; //7
        constexpr int th_horizontal_back_left_pin   = 2; //2
        constexpr int th_horizontal_back_right_pin  = 5; //5
        constexpr int th_vertical_front_pin         = 4; //4
        constexpr int th_vertical_back_pin          = 3; //3

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
//        constexpr int manip_grab_ch     = 1;
//        constexpr int manip_release_ch   = 0;
//
//        constexpr int manip_left_ch     = 2;
//        constexpr int manip_right_ch    = 3;

        constexpr int manip_grab_ch     = 2;
        constexpr int manip_release_ch   = 3;

        constexpr int manip_left_ch     = 0;
        constexpr int manip_right_ch    = 1;
    }

    /* indices of thrusters (controlled by SAMD_ISR_SERVO) */
    namespace thrusters {
        enum thrusters {
            horizontal_front_left = 0,
            horizontal_front_right,
            horizontal_back_left,
            horizontal_back_right,
            vertical_front,
            vertical_back,
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
        extern uint8_t debug_mode;
        constexpr bool standalone = 1;					//turns off most of the external devices, allowing "clean" initialisation without any connections 
        constexpr bool force_ethernet_init = 0;		    //forcibly turns on the Ethernet controller present on the board. WARNING, the board can hang when initialising Ethernet controller without proper connection to external Ethernet device
        constexpr bool force_depth_sensor_init = 0;   	//forcibly turns on the depth sensor. for it to work, you need to connect the secondary board with depth sensor present
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
#endif