#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 73, 9);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetClient ethClient;
PubSubClient client;

// Agent identification
String uid;

void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}


	// start the Ethernet connection and the mqtt client
	Ethernet.begin(mac, ip);
	client.setClient(ethClient);
	client.setServer("192.168.73.6", 1883);
	client.connect("I1820-agent");

	// generate agent identification
	uid = "RoomanArduino1";
}


void loop() {
	client.publish("I1820/parham-home/agent/ping", "{}");
	delay(10);
}
