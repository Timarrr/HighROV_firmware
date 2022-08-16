#pragma once

#include "Data.h"
class Thrusters
{
public:
    static void init();
    static void update_thrusters(rov::RovControl & ctrl, rov::RovTelemetry &tel);
    static void set_status(String status);
    static String get_status();
    static String status;
private:
    static Thrusters &inst();
    int directions[6] = { 1,1,1,-1,-1,1 };
};
