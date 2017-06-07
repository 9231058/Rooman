#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
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

// RTP values
String response;
uint16_t sequenceNumber;
uint32_t timestamp;
uint32_t ssrc = "13731376";

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// TFT instance
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

void setup() {
	// start the Ethernet and UDP:
	Ethernet.begin(mac, ip);
	Udp.begin(1373);

	// start serial
	Serial.begin(9600);

	// start tft lcd
	tft.reset();
	tft.begin(0x9481);
}

void loop() {
	// Reset screen
	tft.fillScreen(0x0000);
	tft.setCursor(0, 0);
	tft.setTextColor(0xFFE0);
	tft.setTextSize(1);

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
	tft.println(response);

	char __response[response.length() + 1];
	response.toCharArray(__response, response.length() + 1);
	int l = RTPPacket(__response, sequenceNumber, ssrc, timestamp).serialize(packetBuffer);
	sequenceNumber = (sequenceNumber + 1) % (1 << 16);
	timestamp++;

	Udp.beginPacket(IPAddress(192, 168, 73, 255), 1373);
	Udp.write((const char*)packetBuffer, l);
	Udp.endPacket();

	delay(1000);
}
