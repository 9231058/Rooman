#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <RTPPacket.h>
#include <dht11.h>


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 73, 9);

// RTP packet buffer
unsigned char packetBuffer[255];

// DHT11 sensor instance
dht11 DHT11;

String response;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {
	// start the Ethernet and UDP:
	Ethernet.begin(mac, ip);
	Udp.begin(1373);

	Serial.begin(9600);
}

void loop() {
	// Read pin 2 for DHT11 temperature and humidity
	int chk = DHT11.read(2);
	switch (chk)
	{
		case DHTLIB_OK:
			response = String((float)DHT11.temperature) + "\n" + String((float)DHT11.humidity);
			break;
		case DHTLIB_ERROR_CHECKSUM:
			response = "Checksum error";
			break;
		case DHTLIB_ERROR_TIMEOUT:
			response = "Time out error";
			break;
		default:
			response = "Unknown error";
			break;
	}

	char __response[response.length() + 1];
	response.toCharArray(__response, response.length() + 1);
	int l = RTPPacket(__response, 0, 0).serialize(packetBuffer);

	Udp.beginPacket(IPAddress(192, 168, 73, 255), 1373);
	Udp.write((const char*)packetBuffer, l);
	Udp.endPacket();

	delay(10);
}
