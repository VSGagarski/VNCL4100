/*
 Name:		VCNL4100_Test.ino
 Created:	07.02.2020 20:19:09
 Author:	VSGagarski
*/

#include "VCNL4100.h"
VCNL4100 vcnl4100;



void setup() {
	Serial.begin(9600);
	while (!Serial);
	Serial.println("Booting.");

	vcnl4100.initialize();
}


void loop() {

	Serial.print("Proximity: ");
	Serial.println(vcnl4100.getProximity());
	Serial.print("Ambient: ");
	Serial.println(vcnl4100.getAmbient());

	//Check interrupt pin

	//Set LED to interrupt pin HIGH/LOW
	Serial.print("Interrupt: ");
	Serial.println(vcnl4100.getProxInterrupt());



	Serial.println();
	delay(200);
}
