#include <stdio.h>
#include <stdbool.h>
#include <string>

enum states {
    Disconnected,
    Connected,
    LedsOn,
    LedsOff,
    Morse,
    Random
};
static states State, NextState;
int main(){}

std::string stateMachine2(bool connected, bool lightStatus, bool morseStatus, bool random) {
    //std::string morseText;
    //int dimVal = 60;
    //bool lightStatus = true;
    //bool morseStatus = false;
    //bool connected = false;

    State = Disconnected;
    NextState = Disconnected;
    while (1) {

        State = NextState;
       
        switch (State) {
        case Disconnected:
            if (connected) {           //if connection with wifi
                NextState = Connected;
            }
            else {
                return "Disconnected";
                //NextState = Disconnected;
            }
            break;
        case Connected:
            if (!connected) {  //connection lost
                NextState = Disconnected;
            }
            else if (lightStatus) {//if on button is pressed
                NextState = LedsOn;
            }
            else if (morseStatus) { // Morse
                NextState = Morse;
            }
            else if(random) {
                NextState = Random;
            }
            else { //still connected 
                return "Connected";
                //NextState = Connected;
            }       
        case LedsOn:
            // turn on the configured pins for the leds
            //go to light on function with dimmer value
            printf("Lights on");
            if (!connected) { // connection lost
                NextState = Disconnected;
            }
            else if (morseStatus) {//if morse message Nextstate Morse
                NextState = Morse;
            }
            else if (!lightStatus) { //leds off button
                NextState = LedsOff;
            }
            else if (random) {
                NextState = Random;
            }
            else { //leds still on
                return "LedsOn";
                //NextState = LedsOn;
            }
            break;
        case LedsOff:
            //lightsOff();
            printf("Lights off");
            return "LedsOff";
            NextState = Connected;
            break;
        case Morse:
            //morse function
            morseStatus = false;
            return "Morse";

            if (lightStatus) {
                NextState = LedsOn;
            }
            else if (!lightStatus) {
                NextState = LedsOff;
            }
            break;
        case Random:
            //go to funtion
            random = false;
            return "Random";
            
            if (lightStatus) {
                NextState = LedsOn;
            }
            else if (!lightStatus) {
                NextState = LedsOff;
            }
            break;
        }
    }
}