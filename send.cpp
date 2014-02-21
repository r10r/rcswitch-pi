/*
 Usage: see printUsage()
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

void printUsage()
{
	std::cout << "  Usage: sudo ./send <groupCode> <switchNumber> <command>\n";
	std::cout << "    e.g. sudo ./send 01011 3 1\n";
	std::cout << "         sudo ./send <groupNumber> <switchNumber> <command>\n";
	std::cout << "    e.g. sudo ./send 4 3 0\n";
	std::cout << "         sudo ./send <familyCharacter> <groupNumber> <switchNumber> <command>\n";
	std::cout << "    e.g. sudo ./send c 2 3 1\n";
	std::cout << "\n";
	std::cout << "  Command is 0 for OFF and 1 for ON\n";
	std::cout << "\n";
	std::cout << "  See http://code.google.com/p/rc-switch/wiki/HowTo_OperateLowCostOutlets for more information about supported switches\n";
}

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
	if (wiringPiSetup () == -1) return 1;
	RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(PIN);
	
	if(argc == 4)
	{
		char* sGroup = argv[1];
		int nSwitchNumber = atoi(argv[2]);

		int command  = atoi(argv[3]);
		
		if(strlen(sGroup) > 2)
		{
			//Type A: 10 pole DIP switches
			printf("sending [Type A] groupCode[%s] switchNumber[%i] command[%i]\n", sGroup, nSwitchNumber, command);

			switch(command) {
				case 1:
					mySwitch.switchOn(sGroup, nSwitchNumber);
					break;
				case 0:
					mySwitch.switchOff(sGroup, nSwitchNumber);
					break;
				default:
					printf("command[%i] is unsupported\n", command);
					printUsage();
					return -1;
			}
			return 0;
		} else {
			//Type B: Two rotary/sliding switches
			int nGroupNumber = atoi(sGroup);
			printf("sending [Type B] groupNumber[%i] switchNumber[%i] command[%i]\n", nGroupNumber, nSwitchNumber, command);
			switch(command) {
				case 1:
					mySwitch.switchOn(nGroupNumber, nSwitchNumber);
					break;
				case 0:
					mySwitch.switchOff(nGroupNumber, nSwitchNumber);
					break;
				default:
					printf("command[%i] is unsupported\n", command);
					printUsage();
					return -1;
			}
			return 0;
		}
	}
	else if(argc == 5)
	{
	    //Type C: Intertechno
		char* sFamily = argv[1];
		int nGroup = atoi(argv[2]);
		int nDevice = atoi(argv[3]);
		
		int command = atoi(argv[4]);
    
		printf("sending [Type C] family[%s] groupNumber[%i] switchNumber[%i] command[%i]\n", sFamily, nGroup, nDevice, command);

		switch(command) {
			case 1:
				mySwitch.switchOn(sFamily[0], nGroup, nDevice);
				break;
			case 0:
				mySwitch.switchOff(sFamily[0], nGroup, nDevice);
				break;
			default:
				printf("command[%i] is unsupported\n", command);
				printUsage();
				return -1;
		}
		return 0;
	}
	else
	{
		printUsage();
	}
	return 1;
}