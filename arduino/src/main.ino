#include <SPI.h>
#include <Wire.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <RTPPacket.h>
#include <LiquidCrystal.h>
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

// RTP values
String response;
uint16_t sequenceNumber;
uint32_t timestamp;
uint32_t ssrc = 0x13731376;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// LiquidCrystal
// Digital 4 DB4
// Digital 5 DB5
// Digital 6 DB6
// Digital 7 DB7
// Digital 8 RS
// Digital 9 Enable
// Digital 10 Backlight Control

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
	// start the Ethernet and UDP:
	Ethernet.begin(mac, ip);
	Udp.begin(1373);

	// start serial
	Serial.begin(9600);

	// lcd
	lcd.begin(16, 2);
	lcd.clear();
	lcd.setCursor(0, 0);
}

void loop() {
	// reset lcd
	lcd.setCursor(0, 0);
	lcd.clear();

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
	
	lcd.print(response);

	char __response[response.length() + 1];
	response.toCharArray(__response, response.length() + 1);
	int l = RTPPacket(__response, sequenceNumber, ssrc, timestamp).serialize(packetBuffer);
	sequenceNumber = (sequenceNumber + 1) % (1 << 16);
	timestamp++;

	Udp.beginPacket(IPAddress(192, 168, 73, 255), 1373);
	Udp.write((const char*)packetBuffer, l);
	Udp.endPacket();

	delay(5000);
}
