#pragma once

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "Data.h"
#include "sys/_stdint.h"

class Networking
{
public:
    Networking();
    static void maintain();
    static void init();
    static void read_write_udp(rov::RovTelemetry &tel, rov::RovControl &ctrl);
    static String status();
private:
    static Networking &inst();
    int read(uint8_t *buffer, int size);
    void write(uint8_t *buffer, int size);


    byte mac[6] = {
        0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
    };
    EthernetUDP Udp;
   

    IPAddress m_self_ip;
    uint16_t m_self_port; 
    IPAddress m_remote_ip;
    uint16_t m_remote_port;
};
