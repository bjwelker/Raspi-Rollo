/*
 Usage: ./sendv2 <systemCode>
This is only needed for the Raspi-Rollo webapp
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    char* systemCode = argv[1];
    
    if (wiringPiSetup () == -1) return 1;
	printf("sending QuadState[%s]\n", systemCode);
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
	mySwitch.setProtocol(4);
	mySwitch.sendQuadState(systemCode);
	return 0;
}
