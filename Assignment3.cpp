/**
Assignment 3
Lucas Black
113065454
*/
#include "mbed.h"
BusOut display(p5,p6,p7,p8,p9,p10,p11,p12);
DigitalIn swCurrent(p21,PullDown);
DigitalIn swHigh(p23,PullDown);
DigitalIn swReset(p25,PullDown);
AnalogIn tempReader(p19);

//variables to store current temperature and highest temperature recorded
float tempCurrent = 0.0;
float highTemp = 0.0;

//gets the current temperature as an average of 1000 readings
float getCurrentTemp()
{
    //total temperature sum
    float total = 0;
    //temperature taken in
    float temp = 0;
    //runs through 1000 samples and sums the readings together
    for(int i = 0; i < 1000; i++) {
        temp = ((tempReader*3.3)-0.500)/(0.010);
        total += temp;
    }
    //average current temperature of 1000 readings
    tempCurrent = total/1000;

    //rounds number to nearest 10th place
    tempCurrent = float(int(tempCurrent * 10 + 0.5)) / 10;

    return tempCurrent;
}
//Displays the specified number 0 - 9 on the LED display
void displayNum(int num)
{

     switch (num) {
        default:
            display = 0b00000000; //displays blank
            break;
        case 0:
            display = 0b0111111; //displays 0
            break;
        case 1:
            display = 0b0000110; //displays 1
            break;
        case 2:
            display = 0b1011011; //displays 2
            break;
        case 3:
            display = 0b1001111; //displays 3
            break;
        case 4:
            display = 0b1100110; //displays 4
            break;
        case 5:
            display = 0b1101101; //displays 5
            break;
        case 6:
            display = 0b1111101; //displays 6
            break;
        case 7:
            display = 0b0100111; //displays 7
            break;
        case 8:
            display = 0b1111111; //displays 8
            break;
        case 9:
            display = 0b1100111; //displays 9
            break;
    }
    wait(0.8);
    //outputs blank display for .1 second
    display = 0b0000000;
    wait(0.1);

}
//Displays the temperature passed in
void displayTemp(float temp)
{
    int num =  temp * 10;

    //3 digit number
    if(temp >= 10) {
        int tenths = num%10; //gets 10ths place number
        int ones = ((num - tenths)/10)%10; //gets ones place number
        int tens = (((num - tenths)/10) - ones)/10; //gets tens place number
        displayNum(tens); 
        displayNum(ones);
        display = 0b10000000; //displays decimal point
        wait(.8);
        displayNum(tenths); 
    }

    //2 digit number
    else if(temp >= 0) {
        int tenths = num % 10;
        int ones = ((num - tenths)/10)%10;
        displayNum(ones);
        display = 0b10000000;
        wait(.8);
        displayNum(tenths);
    }
    //negative 3 digit number
    else if(temp <= -10) {
        num = num *(-1);
        int tenths = num % 10;
        int ones = ((num - tenths)/10)%10;
        int tens = (((num - tenths)/10) - ones)/10;
        display = 0b1000000; //displays negative sign
        wait(.8);
        displayNum(tens);
        displayNum(ones);
        display = 0b10000000;
        wait(.8);
        displayNum(tenths);
    }
    //negative 2 digit number
    else if(temp < 0) {
        num = num * (-1);
        int tenths = num % 10;
        int ones = ((num - tenths)/10)%10;
        display = 0b1000000;
        wait(.8);
        displayNum(ones);
        display = 0b10000000;
        wait(.8);
        displayNum(tenths);
    }

}


int main()
{
    int state = 0;

    while(1) {
        //always get the current temperature
        tempCurrent = getCurrentTemp();
        
        //checks if current temp is greater than highest recorded temp 
        //and assigns current to highest if true
        if(tempCurrent > highTemp) {
            highTemp = tempCurrent;
        }

        //button pressed, may require holding down for an entire cycle
        //switches to current temperature mode
        if(swCurrent == 1) {
            state = 0;
        }
        //switches to Record High Temperature mode
        if(swHigh == 1) {
            state = 1;
        }
        //resets the high temp to the current temp
        if(swReset == 1) {
            highTemp = tempCurrent;
        }

        //Switches the state to be displayed
        //Current Temperature mode
        if(state == 0) {
            displayTemp(tempCurrent);
            display = 0b111001; //displays C
            wait(0.8);
        }
        //Record High Temperature mode
        if(state == 1) {
            displayTemp(highTemp);
            display = 0b1110110; //displays H
            wait(0.8);
        }

    }
}
