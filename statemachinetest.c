typedef enum{
    Disconnected,
    Connected,
    LedsOn,
    LedsOff,
    Morse,
    Dimmer
} states;

static states State, NextState;
/*static int led1 = //pin nr
static int led2 = //pin nr
static int led3 = //pin nr*/

void stateMachine(void){

State = Disconnected;
NextState = Disconnected;

while(1){
    State = NextState;
    int dimVal = getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/");

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
            else if(getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/lightStatus")){//if on button is pressed
                NextState = LedsOn;
            }
            else if(getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseStatus")){ // Morse
                NextState = Morse;
            }
            else{ //still connected 
                NextState = Connected;
            }
        break;
        case LedsOn:
        // turn on the configured pins for the leds
        //go to light on function
        lightsOn();
            if(WiFi.status() != WL_CONNECTED){ // connection lost
                NextState = Disconnected;
            }
            else if(getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseStatus")){//if morse message Nextstate Morse
                NextState = Morse;
            }
            else if(!getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/lightStatus") ){ //leds off button
            NextState = LedsOff;
            }
            else if(getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/") != dimVal){
               NextState = Dimmer; 
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
        string sendToMorse = getStringFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseText");
        morseSignal(sendToMorse);
        sendBoolToFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseStatus",false);

        if (getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/lightStatus")){
        NextState = LedsOn;
        }
        else if(!getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/lightStatus")){ 
            NextState= LedsOff;
        }
        break;
        case Dimmer:
        dimVal = getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/");//retrieve value from firebase
        // call on dimmer function with value from firebase
        NextState = LedsOn;
        break;
    }
}
}