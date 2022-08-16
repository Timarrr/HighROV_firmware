#include "Networking.h"
#include "Config.h"

void Networking::init() {
    Ethernet.init(config::networking::cs_pin);
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      SerialUSB.println("Ethernet controller was not found. This usually indicates problems with the chip or the PCB");
    }
    else if (Ethernet.hardwareStatus() == EthernetW5100) {
      SerialUSB.println("W5100 Ethernet controller detected.");
    }
    else if (Ethernet.hardwareStatus() == EthernetW5200) {
      SerialUSB.println("W5200 Ethernet controller detected.");
    }
    else if (Ethernet.hardwareStatus() == EthernetW5500) {
      SerialUSB.println("W5500 Ethernet controller detected.");
    }
    SerialUSB.println(Ethernet.begin(inst().mac)==1 ? "Ethernet init success" : "Ethernet init failed");
    inst().Udp.begin(inst().m_self_port);
}

void Networking::read_write_udp(rov::RovTelemetry &tel, rov::RovControl &ctrl) {
    static unsigned long lastTimestamp = 0;
    static constexpr size_t buffer_size = 128;

    uint8_t buffer[buffer_size];
    int size = inst().read(buffer, buffer_size);

    if (size > 0) {
        auto error = ctrl.fromRovControlMsg(buffer, size);

        if (error != rov::RovControl::RovControlErrorCode::NoError) {
            SerialUSB.println(ctrl.fromErrorToString(error));
        }

        if (ctrl.version == 2) {
            size = tel.toRovTelemetryMsgV2(buffer);
        } else {
            size = tel.toRovTelemetryMsgV1(buffer);
        }

        inst().write(buffer, size);

        unsigned long curTimestamp = millis();
        if (abs(curTimestamp - lastTimestamp) > 1000) {
            lastTimestamp = curTimestamp;

            size = rov::RovHello::toRovHelloMsg(buffer);
            inst().write(buffer, size);
        }
    }
}


Networking & Networking::inst() {
    static Networking net;
    return net;
}

int Networking::read(uint8_t * buffer, int size) {
    int packetSize = Udp.parsePacket();

    if (packetSize) {
        Udp.read(buffer, size);
        return packetSize;
    }
    return 0;
}

void Networking::write(uint8_t * buffer, int size) {
    Udp.beginPacket(m_remote_ip, m_remote_port);
    Udp.write(buffer, size);
    Udp.endPacket();
}

String Networking::ip_decoder(uint32_t addr){
    byte ip_buf[4]; // 111.222.333.444
	for(int i = 3; i >= 0; i--){ //byte segment
		for(int j = 7; j >=0; j--){ //bit
			ip_buf[i] += bitRead(addr, i*8+j) * pow(2,j); //bit read order - LSB first -> reading MSB first
		}
	}
    return String(ip_buf[0]) + "." + String(ip_buf[1]) + "." + String(ip_buf[2]) + "." + String(ip_buf[3]) + "." ;
}

String Networking::status() {
    using namespace config::networking;

    return "\nTarget IP:        " + String(selfip[0]) + "." + String(selfip[1]) + "." + String(selfip[2]) + "." + String(selfip[3]) + "\n"\
           "Current IP:         " + ip_decoder(Ethernet.localIP()) + "\n"\
           "DNS server IP:      " + ip_decoder(Ethernet.dnsServerIP()) + "\n"\
           "Gateway IP:         " + ip_decoder(Ethernet.gatewayIP()) + "\n"\
           "Subnet mask:        " + ip_decoder(Ethernet.subnetMask()) + "\n"\
           "Link status:        " + (Ethernet.linkStatus() ? "ON\n" : "OFF\n");

}

Networking::Networking() {
    auto &sp = config::networking::selfip;
    m_self_ip = IPAddress(sp[0], sp[1], sp[2], sp[3]);
    m_self_port = config::networking::self_port;

    auto &rp = config::networking::remoteip;
    m_remote_ip = IPAddress(rp[0], rp[1], rp[2], rp[3]);
    m_remote_port = config::networking::remote_port;
}
