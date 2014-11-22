/*
 Usage:
  1) ./send <systemCode> <unitCode> <command>
  2) ./send <familyGroup> <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 output PIN is hardcoded for testing purposes
 see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
 for pin mapping of the raspberry pi GPIO connector
 */
#define PIN 17

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("usage: send <type> <arg1> ... <argN>\n");
        printf("  type - the type to use for sending the signal\n");
        printf("  arg1 .. argN - depending on the type the list of arguments\n");
        printf("\n");
        printf("Supported types:\n");
        printf("  dip - Switches controlled by DIP switches\n");
        printf("        arg1 - the system code\n");
        printf("        arg2 - the unit code\n");
        printf("        arg3 - command\n");
        printf("        Example: ./send dip 00001 2 0\n");
        printf("\n");
        printf("  rev - Switches from REV manufactor\n");
        printf("        arg1 - the channel (a..f)\n");
        printf("        arg2 - the device number\n");
        printf("        arg3 - command\n");
        printf("        Example: ./send dip a 2 0\n");
        return -1;
    }

    
    if (wiringPiSetupSys () == -1) {
        printf("WiringPiSetup failed!\n");
        return 1;
    }

	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);

    if (strcmp(argv[1], "dip") == 0) {
        char* systemCode = argv[2];
        int unitCode = atoi(argv[3]);
        int command  = atoi(argv[4]);

        printf("sending systemCode[%s] unitCode[%i] command[%i]\n", systemCode, unitCode, command);

        if (command == 1) {
            mySwitch.switchOn(systemCode, unitCode);
            return 0;
        } else if (command == 0) {
            mySwitch.switchOff(systemCode, unitCode);
            return 0;
        }

    } else if (strcmp(argv[1], "rev") == 0) {
        char* channel = argv[2];
        int device = atoi(argv[3]);
        int command  = atoi(argv[4]);

        printf("sending channel[%c] device[%i] command[%i]\n", channel[0], device, command);

        if (command == 1) {
            mySwitch.switchOn(channel[0], device);
            return 0;
        } else if (command == 0) {
            mySwitch.switchOff(channel[0], device);
            return 0;
        }

    }

    printf("Unsupported invocation!\n");
    return 1;
}
