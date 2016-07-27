/*
 * Bauhn (aldi) wireless power switch control.
 *
 * This program sends on/off codes for an inexpensive 4-unit remote power
 * switch set sold by Aldi, replicating the ability of the supplied remote which
 * has separate on and off buttons for each of 4 units,
 * and a 5th pair for all-on/all-off.
 *
 * Usage: sudo ./send_bauhn <command> <unit> <set>
 *
 * Command is 0 for turn-off and 1 for turn-on (or the words 'off' or 'on')
 * Unit is 0 for all units (or 'all'), or 1-4 for individual unit
 * Set is needed if you have more than one set of outlets.
 *
 * If arguments are omitted, the defaults are
 *    command=ON unit=ALL set=1
 *
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Set the TRANSMIT_PIN here
 * see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
 * for pin mapping of the raspberry pi GPIO connector
 */
#define TRANSMIT_PIN 0

/*
 * edit bauhn_codes.h to set the codes for your remote(s)
 */
#include "bauhn_codes.h"

int main(int argc, char *argv[]) {

    int command = 1;
    int unit = 0;
    int set = 1;
    unsigned long code;

    if (wiringPiSetup () == -1) {
            printf("WiringPi setup failed\n");
            exit(1);
    }

    if (argc > 1) {
            if (strcasecmp(argv[1], "on") == 0) command = 1;
            else if (strcasecmp(argv[1], "off") == 0) command = 0;
            else command = atoi(argv[1]);
    }
    if ((command < 0) || (command > 1)) {
            printf("Invalid command value, expected [0,off,1,on]\n");
            exit(1);
    }
    if (argc > 2) {
            if (strcasecmp(argv[2], "all") == 0) unit = 0;
            else unit = atoi(argv[2]);
    }
    if ((unit < 0) || (unit > 4)) {
            printf("Invalid unit value, expected [0,4]\n");
            exit(1);
    }
    if (argc > 3) {
            set = atoi(argv[3]);
    }
    if ((set < 1) || (set > NUM_SETS)) {
            printf("Invalid set value, expected [0,4]\n");
            exit(1);
    }

    printf("sending command %d to unit %d of set %d\n", command, unit, set);

    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableTransmit(TRANSMIT_PIN);

    code = bauhn_codes[set-1][unit][command];
    printf("    transmit code %lu\n", code);

    mySwitch.setProtocol(1);
    mySwitch.setRepeatTransmit(14);
    mySwitch.send(code, 32);

    return 0;
}
