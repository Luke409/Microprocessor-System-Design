#include "mbed.h"


// Registers for port 0
#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)
#define FIO0SET (*(volatile unsigned int *)0x2009c018)
#define FIO0CLR (*(volatile unsigned int *)0x2009c01C)

// Registers for port 1
#define FIO1DIR (*(volatile unsigned int *)0x2009c020)
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)
#define FIO1SET (*(volatile unsigned int *)0x2009c038)
#define FIO1CLR (*(volatile unsigned int *)0x2009c03C)

//Registers for port 2
#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)
#define FIO2SET (*(volatile unsigned int *)0x2009c058)
#define FIO2CLR (*(volatile unsigned int *)0x2009c05C)

//Pinmodes for ports 0 - 2
#define PINMODE0 (*(volatile unsigned int *)0x4002c040)
#define PINMODE1 (*(volatile unsigned int *)0x4002c044)
#define PINMODE2 (*(volatile unsigned int *)0x4002c048)
#define PINMODE4 (*(volatile unsigned int *)0x4002c050)
#define PINMODE3 (*(volatile unsigned int *)0x4002c04c)
#define PINMODE5 (*(volatile unsigned int *)0x4002c054)



int main()
{
    //configure LED4 on mbed to be the output
    FIO1DIR |= (1<<23);

    //turns LED 4 ON at startup
    FIO1PIN |= ~(1<<23);

    //Changes the 2 bits for port 2 pin 5 to 11 -> pull down activated
    PINMODE4 |= (1<<10) | (1<<11);

    //setting pin 2 to input
    FIO2DIR &= ~(1<<5);

    //setting pin 1 to input
    FIO0DIR &= ~(1<<9);


    while(1) {

        //if switch at pin 21 is pressed
        if(((FIO2PIN>>5) & 1) == 1) {
            FIO1PIN |=  (1<<23); //switches LED 4 high
        }

        //if switch at pin 5 is pressed
        if (((FIO0PIN>>9) & 1) == 0) {
            FIO1PIN &= ~(1<<23); //switches LED 4 low
        }

    }

}
