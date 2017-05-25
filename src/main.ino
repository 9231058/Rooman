#include <SPI.h>
#include <Ethernet.h>
#include <WebServer.h>


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 73, 9);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// This creates an instance of the webserver.  By specifying a prefix
// of "", all pages will be at the root of the server.
#define PREFIX ""
WebServer webserver(PREFIX, 80);


void helloCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
	// this line sends the standard "we're all OK" headers back to the browser
	server.httpSuccess();

	// if we're handling a GET or POST, we can output our data here.
	// For a HEAD request, we just stop after outputting headers.
	if (type != WebServer::HEAD)
	{
		/* this defines some HTML text in read-only memory aka PROGMEM.
		 * This is needed to avoid having the string copied to our limited
		 * amount of RAM. */
		P(helloMsg) = "Hello form arduino";

		/* this is a special form of print that outputs from PROGMEM */
		server.printP(helloMsg);
	}
}


void setup() {
	// Initialize the Ethernet adapter
	Ethernet.begin(mac, ip);

	// /hello -> helloCmd
	webserver.addCommand("hello", &helloCmd);

	// start the webserver
	webserver.begin();

}


void loop() {
	char buff[64];
	int len = 64;

	// process incoming connections one at a time forever
	webserver.processConnection(buff, &len);
}
