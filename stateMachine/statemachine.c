#include <stdio.h>
#include <stdbool.h>

enum states{
    Disconnected,
    Connected,
    LedsOn,
    LedsOff,
    Morse,
    RandomBlink
};
static states State, NextState;
void stateMachine(void){

State = Disconnected;
NextState = Disconnected;
while(1){

    State = NextState;
    int dimVal = getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/dimmer");
    delay(1);
    bool lightStatus = getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/lightStatus");
    delay(1);
    bool morseStatus = getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseStatus");
    delay(1);
    string morseText = getStringFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseText");
    delay(1);
    bool blink = getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/blinkSent");
    delay(1);
    
    switch (State){
        case Disconnected:
        if(WiFi.status() == WL_CONNECTED){           //if connection with wifi
        NextState = Connected;
        }
        else{
        NextState = Disconnected;
        }
        break;
        case Connected:
            if(WiFi.status() != WL_CONNECTED){  //connection lost
                NextState = Disconnected;
            }
            else if(lightStatus){//if on button is pressed
                NextState = LedsOn;
            }
            else if(morseStatus){ // Morse
                NextState = Morse;
            }
            else if(blink){
                NextState = RandomBlink;
            }
            else{ //still connected 
                NextState = Connected;
            }
        break;
        case LedsOn:
        //go to light on function with dimmer value
        lightsOn(dimVal);
            if(WiFi.status() != WL_CONNECTED){ // connection lost
                NextState = Disconnected;
            }
            else if(morseStatus){//if morse message Nextstate Morse
                NextState = Morse;
            }
            else if(!lightStatus){ //leds off button
                NextState = LedsOff;
            }
            else if(blink){
                NextState = RandomBlink;
            }
            else{ //leds still on
                NextState = LedsOn;
            }
        break;
        case LedsOff:
        lightsOff();
        NextState = Connected;
        break;
        case Morse:
        char* sendToMorse = stringToCharArray(morseText);
        morseSignal(sendToMorse);
        delay(1);
        sendBoolToFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseStatus",false);

        if (lightStatus){
        NextState = LedsOn;
        }
        else if(!lightStatus){ 
            NextState= LedsOff;
        }
        break;
        case RandomBlink:
        delay(1);
        int timer = getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/blinkTimer");
         //got to blink function
        delay(1);   
        sendBoolToFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/"blinkSent,false);    
         
        if (lightStatus){
        NextState = LedsOn;
        }
        else if(!lightStatus){ 
            NextState= LedsOff;
        }  
        break;
    }
}
}
