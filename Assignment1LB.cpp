#include "mbed.h"
DigitalIn swBR(p5, PullUp);
DigitalIn swGR(p10, PullUp);
DigitalIn swGB(p30, PullDown);

//initializing all leds to on, 1 = on for green/blue, 0 = on for red led
DigitalOut gLed1(p18,1);
DigitalOut gLed2(p19,1);
DigitalOut gLed3(p20,1);
DigitalOut rLed1(p23,0);
DigitalOut rLed2(p22,0);
DigitalOut rLed3(p21,0);
DigitalOut bLed1(LED1,1);
DigitalOut bLed2(LED2,1);
DigitalOut bLed3(LED3,1);
DigitalOut bLed4(LED4,1);

//Creating blue, red, and green states used to switch certain leds off depending on current state
int blueState;
int redState;
int greenState;

int main()
{

    while(1) {
        //when the Blue Red switch is pressed, executes the following code
        if(swBR == 0) {
            //incriments the blue and red states by 1 after the button is pressed
            blueState++;
            redState++;

            //since starting at all on, the next state turns off the first blue led
            if(blueState == 1) {
                bLed1 = 0;
                bLed2 = 1;
                bLed3 = 1;
                bLed4 = 1;
            } else if(blueState == 2) { //two blue leds off
                bLed1 = 0;
                bLed2 = 0;
                bLed3 = 1;
                bLed4 = 1;
            } else if(blueState == 3) { //3 blue leds off
                bLed1 = 0;
                bLed2 = 0;
                bLed3 = 0;
                bLed4 = 1;
            } else if(blueState == 4) { //all blue leds off
                bLed1 = 0;
                bLed2 = 0;
                bLed3 = 0;
                bLed4 = 0;
            } else { //resets the blue leds to ALL ON after button is pressed and leds are all off
                bLed1 = 1;
                bLed2 = 1;
                bLed3 = 1;
                bLed4 = 1;
                blueState = 0;
            }

            //Red states following same logic as blue LEDs except with 3 states instead of 4
            if(redState == 1) {
                rLed1 = 1;
                rLed2 = 0;
                rLed3 = 0;
            } else if(redState == 2) {
                rLed1 = 1;
                rLed2 = 1;
                rLed3 = 0;
            } else if(redState == 3) {
                rLed1 = 1;
                rLed2 = 1;
                rLed3 = 1;
            } else { //resets the red LEDS to all after button is pressed and the LEDS are all off
                redState = 0;
                rLed1 = 0;
                rLed2 = 0;
                rLed3 = 0;
            }

            //waits 200ms to allow for better human interaction
            wait(.2);

        }

        //When Green Red Switch is pressed, following statements are executed
        if(swGR == 0) {

            //incriments the green and red states
            greenState++;
            redState++;

            //Green State follows similar logic as the red state logic in BR switch
            if(greenState == 1) {
                gLed1 = 0;
                gLed2 = 1;
                gLed3 = 1;

            } else if(greenState == 2) {
                gLed1 = 0;
                gLed2 = 0;
                gLed3 = 1;

            } else if(greenState == 3) {
                gLed1 = 0;
                gLed2 = 0;
                gLed3 = 0;
            } else {
                gLed1 = 1;
                gLed2 = 1;
                gLed3 = 1;
                greenState = 0;
            }

            //Continues red state logic when button is pressed
            if(redState == 1) {
                rLed1 = 1;
                rLed2 = 0;
                rLed3 = 0;
            } else if(redState == 2) {
                rLed1 = 1;
                rLed2 = 1;
                rLed3 = 0;
            } else if(redState == 3) {
                rLed1 = 1;
                rLed2 = 1;
                rLed3 = 1;
            } else {
                redState = 0;
                rLed1 = 0;
                rLed2 = 0;
                rLed3 = 0;
            }

            wait(.2);
        }

        //When Green Blue switch is pressed, following logic is executed
        if(swGB == 1) {
            //increases green and blue states
            greenState++;
            blueState++;

            //Continues the Blue State logic when button is pressed
            if(blueState == 1) {
                bLed1 = 0;
                bLed2 = 1;
                bLed3 = 1;
                bLed4 = 1;
            } else if(blueState == 2) {
                bLed1 = 0;
                bLed2 = 0;
                bLed3 = 1;
                bLed4 = 1;
            } else if(blueState == 3) {
                bLed1 = 0;
                bLed2 = 0;
                bLed3 = 0;
                bLed4 = 1;
            } else if(blueState == 4) {
                bLed1 = 0;
                bLed2 = 0;
                bLed3 = 0;
                bLed4 = 0;
            } else {
                bLed1 = 1;
                bLed2 = 1;
                bLed3 = 1;
                bLed4 = 1;
                blueState = 0;
            }
            
            //Continues green state logic when button is pressed
            if(greenState == 1) {
                gLed1 = 0;
                gLed2 = 1;
                gLed3 = 1;

            } else if(greenState == 2) {
                gLed1 = 0;
                gLed2 = 0;
                gLed3 = 1;

            } else if(greenState == 3) {
                gLed1 = 0;
                gLed2 = 0;
                gLed3 = 0;
            } else {
                gLed1 = 1;
                gLed2 = 1;
                gLed3 = 1;
                greenState = 0;
            }

            wait(0.2);

        }

    }

}







