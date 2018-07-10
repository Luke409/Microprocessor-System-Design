#include "mbed.h"

//Declaring all Inputs/Outputs, as well as tickers and timers
DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);
Timer t;
Ticker ticker;
InterruptIn right1(p28);
InterruptIn right2(p23);
InterruptIn left1(p15);
InterruptIn left2(p18);

int p1pos = 0; //Position of player 1
int p2pos = 0;  //Position of player 2
int lastLeft = 0; //keeps track of the last left button that was pressed
int lastRight = 0; //keeps track of the last right button that was pressed

//display method displays the position of both players and if the position threshold is surpassed it will display the winner and the
//time it took to reach the finish line
void display()
{
    //if player 1 reaches 40, it will display the time it took and announce that Player 1 won
    if( p1pos == 40) {
        pc.printf("Player 1 is the winner!  ");
        pc.printf("Time elapsed: %.2f seconds", t.read());
        t.stop();
        ticker.detach();
    } else if(p2pos == 40) { //if player 2 reaches 40, player 2 wins and time is announced
        pc.printf("Player 2 is the winner!  ");
        pc.printf("Time elapsed: %.2f seconds", t.read());
        t.stop();
        ticker.detach();
    } else { //Otherwise, displays the current position of the two players
        pc.printf("Player 1 position: %d        ", p1pos);
        pc.printf("Player 2 position: %d\n\r", p2pos);
    }
}

//Increases the position of Player 2 if button right1 wasnt recently pressed
void increaseRight1()
{
    if(lastRight != 1) { //if last button pressed was not right1
        if(p1pos == 40) { //waits so winner can be displayed
            wait(.025);
        } else {
            lastRight = 1; //changes last button pressed to right1
            p1pos++; //incriments the position
        }
    } else //if last button pressed was right 1, then do nothing and wait
        wait(0.025);
}
//Increases the position of Player 2 if button right2 wasnt recently pressed
void increaseRight2()
{
    if(lastRight != 2) {
        if(p1pos == 40) {
            wait(.025);
        } else {
            lastRight = 2;
            p1pos++;
        }
    } else
        wait(0.025);
}
//Increases the position of Player 1 if button left1 wasnt recently pressed
void increaseLeft1()
{
    if(lastLeft != 1) {
        if(p2pos == 40) {
            wait(.025);
        } else {
            lastLeft = 1;
            p2pos++;
        }
    } else
        wait(0.025);
}
//Increases the position of Player 1 if button left2 wasnt recently pressed
void increaseLeft2()
{
    if(lastLeft != 2) {
        if(p2pos == 40) {
            wait(.025);
        } else {
            lastLeft = 2;
            p2pos++;
        }
    } else
        wait(0.025);
}

int main()
{
    left1.mode(PullUp); //setting switch to pull up
    left2.mode(PullUp);
    right1.mode(PullDown); //setting switch to pull down
    right2.mode(PullDown);

    right1.rise(&increaseRight1); //sets the right button 1 to trigger on rise (when button is pressed)
    right2.rise(&increaseRight2);
    left1.fall(&increaseLeft1); //sets the left button 1 to trigger on fall (when button is pressed)
    left2.fall(&increaseLeft2);
    
    pc.baud(9600); //setting baud rate

    pc.printf("On your marks!\n\r");
    wait(1);
    pc.printf("Get set!\n\r");
    wait(1);
    pc.printf("Go!\n\r");

    t.start(); //starts the timer after Go!

    ticker.attach(&display,1); //uses the ticker to update/display the current position of the players every 1 second
}

