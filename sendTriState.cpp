/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
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
    char* tristate = argv[1];
    
    if (wiringPiSetup () == -1) return 1;
	printf("sending tristate[%s] \n", tristate);
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
    mySwitch.setPulseLength(360);

    mySwitch.sendTriState(tristate);

	return 0;
}
