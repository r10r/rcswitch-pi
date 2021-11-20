/*
 Usage: ./send    <command>
 SystemCodeType is 1 for default and 2 for switches with 10 Bits 123456ABCD
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

 /*
 output PIN is hardcoded for testing purposes
 see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
 for pin mapping of the raspberry pi GPIO connector
 */
 int PIN = 1; // GPIO-PIN 17
 int systemCodeType = atoi(argv[1]);
 char* systemCode = argv[2];
 int unitCode = atoi(argv[3]);
 int command = atoi(argv[4]);
 char pSystemCode[14];

 if (wiringPiSetup () == -1) return 1;
 printf("sending systemCodeType[%i] systemCode[%s] unitCode[%i] command[%i] ...\n", systemCodeType, systemCode, unitCode, command);
 RCSwitch mySwitch = RCSwitch();
 printf("defining transmit PIN[%i] ... ",PIN);
 mySwitch.enableTransmit(PIN);
 printf("success\n");
 printf("computing system Code Type ...\n");
 switch(systemCodeType)
    {
     case 1:
        {
         printf("Switching \"default\" system[%s] unit[%i] ... ", systemCode, unitCode);
         switch(command)
            {
             case 0:
                {
                printf("off\n");
                mySwitch.switchOff(systemCode, unitCode);
                break;
                }
             case 1:
                {
                printf("on\n");
                mySwitch.switchOn("00011", unitCode);
                break;
                }
             default:
                {
                printf("command[%i] is unsupported\n", command);
                return -1;
                }
            }
        break;
        }
     case 2:
        {
        printf("computing systemcode for Intertechno Type B house[%i] unit[%i] ... ",atoi(systemCode), unitCode);
        switch(atoi(systemCode))
            {
            // house/family code A=1 - P=16
            case 1:     { printf("1/A ... ");       strcpy(pSystemCode,"0000"); break; }
            case 2:     { printf("2/B ... ");       strcpy(pSystemCode,"F000"); break; }
            case 3:     { printf("3/C ... ");       strcpy(pSystemCode,"0F00"); break; }
            case 4:     { printf("4/D ... ");       strcpy(pSystemCode,"FF00"); break; }
            case 5:     { printf("5/E ... ");       strcpy(pSystemCode,"00F0"); break; }
            case 6:     { printf("6/F ... ");       strcpy(pSystemCode,"F0F0"); break; }
            case 7:     { printf("7/G ... ");       strcpy(pSystemCode,"0FF0"); break; }
            case 8:     { printf("8/H ... ");       strcpy(pSystemCode,"FFF0"); break; }
            case 9:     { printf("9/I ... ");       strcpy(pSystemCode,"000F"); break; }
            case 10:    { printf("10/J ... ");      strcpy(pSystemCode,"F00F"); break; }
            case 11:    { printf("11/K ... ");      strcpy(pSystemCode,"0F0F"); break; }
            case 12:    { printf("12/L ... ");      strcpy(pSystemCode,"FF0F"); break; }
            case 13:    { printf("13/M ... ");      strcpy(pSystemCode,"00FF"); break; }
            case 14:    { printf("14/N ... ");      strcpy(pSystemCode,"F0FF"); break; }
            case 15:    { printf("15/O ... ");      strcpy(pSystemCode,"0FFF"); break; }
            case 16:    { printf("16/P ... ");      strcpy(pSystemCode,"FFFF"); break; }
            default:
                {
                printf("systemCode[%s] is unsupported\n", systemCode);
                return -1;
                }
            }
        printf("got systemCode\n");
        switch(unitCode)
        {
        // unit/group code 01-16
            case 1:     { printf("1 ... ");     strcat(pSystemCode,"0000"); break; }
            case 2:     { printf("2 ... ");     strcat(pSystemCode,"F000"); break; }
            case 3:     { printf("3 ... ");     strcat(pSystemCode,"0F00"); break; }
            case 4:     { printf("4 ... ");     strcat(pSystemCode,"FF00"); break; }
            case 5:     { printf("5 ... ");     strcat(pSystemCode,"00F0"); break; }
            case 6:     { printf("6 ... ");     strcat(pSystemCode,"F0F0"); break; }
            case 7:     { printf("7 ... ");     strcat(pSystemCode,"0FF0"); break; }
            case 8:     { printf("8 ... ");     strcat(pSystemCode,"FFF0"); break; }
            case 9:     { printf("9 ... ");     strcat(pSystemCode,"000F"); break; }
            case 10:    { printf("10 ... ");        strcat(pSystemCode,"F00F"); break; }
            case 11:    { printf("11 ... ");        strcat(pSystemCode,"0F0F"); break; }
            case 12:    { printf("12 ... ");        strcat(pSystemCode,"FF0F"); break; }
            case 13:    { printf("13 ... ");        strcat(pSystemCode,"00FF"); break; }
            case 14:    { printf("14 ... ");        strcat(pSystemCode,"F0FF"); break; }
            case 15:    { printf("15 ... ");        strcat(pSystemCode,"0FFF"); break; }
            case 16:    { printf("16 ... ");        strcat(pSystemCode,"FFFF"); break; }
            default:
            {
            printf("unitCode[%i] is unsupported\n", unitCode);
            return -1;
            }
         }
        strcat(pSystemCode,"0F"); // mandatory bits
        switch(command)
        {
             case 0:
                 {
                 strcat(pSystemCode,"F0");
                 mySwitch.sendTriState(pSystemCode);
                 printf("sent TriState signal: pSystemCode[%s]\n",pSystemCode);
                 break;
                 }
             case 1:
                 {
                 strcat(pSystemCode,"FF");
                 mySwitch.sendTriState(pSystemCode);
                 printf("sent TriState signal: pSystemCode[%s]\n",pSystemCode);
                 break;
                 }
             default:
                 {
                 printf("command[%i] is unsupported\n", command);
                 return -1;
                 }
            }
            break;
    }
        default:
            {
                printf("command sequence unknown, aborting!\n");
                return -1;
            }
        }
 return 0;
    }
