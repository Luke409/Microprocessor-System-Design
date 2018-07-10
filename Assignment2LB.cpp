#include "mbed.h"
//Declaring the two switches as inputs
DigitalIn sw1(p19, PullDown);
DigitalIn sw2(p20, PullDown);

//Declaring the 4 blue LEDS, 1 red LED, and Piezo as Pulse Width Modulation outputs
PwmOut bLed1(LED1);
PwmOut bLed2(LED2);
PwmOut bLed3(LED3);
PwmOut bLed4(LED4);
PwmOut rLed(p22);
PwmOut piezo(p21);


int main()
{

    while(1) {

        //Executes the following code when switch 1 is pressed
        if(sw1 == 1) {
            //decriments the frequency from 1780Hz by 25Hz down to 880 Hz
            for(int i = 1780; i >= 880; i = i - 25) {
                //produces a tone at a given frequency by setting the period = 1/freq
                piezo.period(1./i);
                //sets the duty cycle to 0.5
                piezo = 0.5;
                //waits in order to correctly decrease the frequency over 0.5 seconds
                wait(.0142045);

                //fades blue led1 on between threshold of 1760 - 1540 Hz
                if(i <= 1760 && i >= 1540 && sw1 ==1) {
                    bLed1= (1760.-i)/(1760.-880);
                    bLed2 = 0;
                    bLed3 = 0;
                    bLed4 = 0;
                }

                //fades blue led 2 on between threshold of 1540 - 1320 Hz
                else if(i<=1540 && i >=1320 && sw1 == 1) {
                    bLed1 = 0;
                    bLed2 = (1760.-i)/(1760.-880);
                    bLed3 = 0;
                    bLed4 = 0;
                }

                //fades blue led 3 on between threshold of 1320 - 1100 Hz
                else if(i<=1320 && i >=1100 && sw1 == 1) {
                    bLed1 = 0;
                    bLed2 = 0;
                    bLed3 = (1760.-i)/(1760.-880);
                    bLed4 = 0;
                }

                //fades blue led 4 on between threshold of 1100 - 880 Hz
                else if(i<=1100 && i >=880 && sw1 == 1) {
                    bLed1 = 0;
                    bLed2 = 0;
                    bLed3 = 0;
                    bLed4 = (1760.-i)/(1760.-880);
                }

            }
        }
        //turns off blue Leds and piezo when switch 1 is not pressed
        else if (sw1 == 0) {
            piezo = 0;
            bLed1 = 0;
            bLed2 = 0;
            bLed3 = 0;
            bLed4 = 0;
            wait(.005);
        }

        //executes following code when switch 2 is pressed
        if(sw2 == 1) {

            //incirments frequency from 440 Hz up to 880 Hz by 25 Hz
            for(int i = 440; i <= 880; i = i + 25) {


                //sets the red led brightness to fade on according to the frequecny
                rLed = (i - 440.)/(440);
                //sets the tone of the piezo
                piezo.period(1./i);
                //sets the duty cycle of the piezo
                piezo = 0.5;

                //if the Frequency is increased past 880Hz, the Piezo makes no noise for 0.5 sec and Led turns off
                if(i >= 880) {
                    rLed = 0;
                    wait(0.5);
                }

                //waits in order to correctly increase LED brightness and piezo frequency over 1 second
                else {
                    wait(0.0568181);
                }

            }

        }
        //when switch 2 is off, the piezo is off and the red led is also turned off
        else if(sw2 ==0) {
            piezo = 0;
            rLed = 0;
            wait(.005);
        }
    }
}