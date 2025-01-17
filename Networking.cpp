#include "Networking.h"
#include "Config.h"
#include "USB/USBAPI.h"

long long last_maintain_time = 0;
bool link_up = false;

void Networking::init() {
	Ethernet.init(config::networking::cs_pin);
	if (Ethernet.hardwareStatus() == EthernetNoHardware) {
	  SerialUSB.println("Ethernet controller was not found. This usually indicates problems with the chip or the PCB. If the next message is \"Ethernet init success\" then you can ignore this message");
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
	SerialUSB.print("Ethernet init... ");
	SerialUSB.println(Ethernet.begin(inst().mac, 10000, 5000)==1 ? "Success!" : "Failed!");
	inst().Udp.begin(inst().m_self_port);
}

void Networking::read_write_udp(rov::RovTelemetry &tel, rov::RovControl &ctrl) {
	static unsigned long lastTimestamp = 0;
	static constexpr size_t buffer_size = 128;

	uint8_t buffer[buffer_size];
	int size = inst().read(buffer, buffer_size);




	if (size > 0) {
        ctrl.fromRovControlMsg(buffer, size);
	}
	size = tel.toRovTelemetryMsgV2(buffer);
	inst().write(buffer, size);
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

String Networking::status() {
	using namespace config::networking;

	SerialUSB.print("\n\r"
					"Target self IP:     " + String(selfip[0]) + "." + String(selfip[1]) + "." + String(selfip[2]) + "." + String(selfip[3]) + "\n\r");
	SerialUSB.print("Current self IP:    "); SerialUSB.println(Ethernet.localIP());
	SerialUSB.print("DNS server IP:      "); SerialUSB.println(Ethernet.dnsServerIP());
	SerialUSB.print("Gateway IP:         "); SerialUSB.println(Ethernet.gatewayIP());
	SerialUSB.print("Subnet mask:        "); SerialUSB.println(Ethernet.subnetMask());
	SerialUSB.print("Link status:        "); SerialUSB.println((Ethernet.linkStatus() ? "ON\n\r" : "OFF\n\r"));

}

void Networking::maintain(){
	if (Ethernet.linkStatus() == LinkON && !link_up) {
		SerialUSB.println("Link status: On");
		link_up = true;
	}
	else if (Ethernet.linkStatus() == LinkOFF && link_up) {
		SerialUSB.println("Link status: Off. This usually indicates problems with cable");
		link_up = false;
	}
	if ((link_up && (millis() >= last_maintain_time + 500)) || millis() >= last_maintain_time + 5000){//if link is up -> check every half a second, otherwise check once every 5 seconds
		byte status = Ethernet.maintain();
		switch(status){
			case 0:
				break;
			case 1:
				SerialUSB.println("DHCP lease renew failed, check the configuration of your DHCP server");
				break;
			case 2:
				SerialUSB.println("DHCP lease renew success");
				break;
			case 3:
				SerialUSB.println("DHCP rebind failed, check the configuration of your DHCP server");
				break;
			case 4:
				if(link_up)
				{
					SerialUSB.println("DHCP rebind detected, this almost certainly will break things");
				}
				else
				{
					String ip = (String) Ethernet.localIP();
					SerialUSB.println("Binding to DHCP address " + ip + " after downtime, check the IP and reboot the router and the ROV if it is incorrect\n\r" + \
										 "If problem persists, check your router and PC's settings");
				}
				break;
			default:
				break;
		}
		last_maintain_time = millis();
	}		
}

Networking::Networking() {
	auto &sp = config::networking::selfip;
	m_self_ip = IPAddress(sp[0], sp[1], sp[2], sp[3]);
	m_self_port = config::networking::self_port;

	auto &rp = config::networking::remoteip;
	m_remote_ip = IPAddress(rp[0], rp[1], rp[2], rp[3]);
	m_remote_port = config::networking::remote_port;
}
