#pragma once

#include "Data.h"
class Thrusters
{
public:
    static void init();
    static void update_thrusters(rov::RovControl & ctrl, rov::RovTelemetry &tel);
    static String get_status();
    static String status;
private:
    static Thrusters &inst();
    int directions[8] = { 1,1,1,1,1,1,1,1 };
};
