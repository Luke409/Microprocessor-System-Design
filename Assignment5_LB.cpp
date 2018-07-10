#include "mbed.h"
#include "cmath"
#include "cstdlib"
SPI spi(p11, p12, p13); // mosi, miso, sclk
Serial pc(USBTX, USBRX);
DigitalOut select1(p14); //chip select for 74HC595
DigitalOut select2(p15);
Timer timer;

int input = 0; //input of used as the result of the button being pressed
int correctSwitch; //switch that should be pressed for the game to continue
float timeLimit; //current time limit to press button

//Changes the letter on the 7 seg display to a Random Letter,
//also returns the correct switch to be pressed
void setRandomLetter(int letter)
{
    switch(letter) {
        case 0: //A
            spi.format(8,0);
            select1 = 0;
            spi.write(0b11101110); //letter A
            select1 = 1;
            correctSwitch = 1;;
            break;

        case 1: //B
            spi.format(8,0);
            select1 = 0;
            spi.write(0b0111110); //letter B
            select1 = 1;
            correctSwitch = 2;
            break;

        case 2: //C
            spi.format(8,0);
            select1 = 0;
            spi.write(0b10011100); //letter C
            select1 = 1;
            correctSwitch = 4;

            break;

        case 3: //C
            spi.format(8,0);
            select1 = 0;
            spi.write(0b01111010); //letter D
            select1 = 1;
            correctSwitch = 8;
            break;
    }
}



int main()
{
    spi.frequency(1000000);
    timeLimit = 1;

    while(1) {
        //go for indefinite rounds

        int randNum = (rand()%4); // sets a random number from 0 - 4
        //   pc.printf("Num= %d\n", randNum);


        //determines the correct switch and also sets the letter of the LED display
        setRandomLetter(randNum);

        timer.reset(); //resets past timer
        timer.start(); //starts the timer
        pc.printf("Num= %d\n", input);
        //checks for inputs while the timer is less than the time limit
        while(timer <= timeLimit && input == 0) {
            spi.format(8,2);
            select2 = 1;
            input = spi.write(0); //sets the input to the button pressed
            select2 = 0;
        }
        timer.stop();

        //If you run out of time or the wrong switch was pressed, display L
        if(timer.read() >= timeLimit || input!= correctSwitch) { //displays L if you lose
            spi.format(8,0);
            select1 = 0;
            spi.write(0b00011100);
            select1 = 1;
            break;
        } else if(input == correctSwitch) {
            pc.printf("Time: %.2f\n", timeLimit);
            timeLimit = timeLimit*(0.8); //reduces the game time by 80%
            input = 0;

        }
        wait(0.3); //waits
    }


}
