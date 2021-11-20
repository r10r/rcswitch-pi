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
    char* sGroup = argv[1];
    int nDevice = atoi(argv[2]);
    int command  = atoi(argv[3]);
    
    if (wiringPiSetup () == -1) return 1;
	printf("sending sGroup[%s] nDevice[%i] command[%i]\n", sGroup, nDevice, command);
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
    //mySwitch.setPulseLength(360);

    switch(command) {
        case 1:
            mySwitch.switchOn(sGroup[0], nDevice);
            break;
        case 0:
            mySwitch.switchOff(sGroup[0], nDevice);
            break;
        default:
            printf("command[%i] is unsupported\n", command);
            return -1;
    }
	return 0;
}
