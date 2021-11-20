/*
 * Off and On codes for Bauhn (Aldi) remote power sockets
 *
 * The units auto-pair to the remote on first use.
 * Use the arduino rc-switch ReceiveDemo program to
 * find out the codes that your individual remotes send,
 * then edit bauhn_codes.h to set the codes for your units.
 *
 */

#define NUM_SETS 1

unsigned long bauhn_codes[NUM_SETS][5][2] = {
    { // first set
        { 3831040116UL, 3831039096UL }, // all-off all-on
        { 3831039866UL, 3831041906UL }, // 1-off 1-on
        { 3831038846UL, 3831040886UL }, // 2-off 2-on
        { 3831039353UL, 3831041393UL }, // 3-off 3-on
        { 3831039611UL, 3831041651UL }  // 4-off 4-on
    }
    // ,{ // second set here if any
    //     { code, code }, etc
    //  }
};

