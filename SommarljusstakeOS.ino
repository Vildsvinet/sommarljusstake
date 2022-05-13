#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

//Network credentials
#define WIFI_SSID "Galaxy A510063"
#define WIFI_PASSWORD "xulz7571"

//User login for firebase
#define USER_EMAIL "valued_customer@sommarljusstake.se"
#define USER_PASSWORD "Secureasfuck123"

//Firebase project API Key
//#define API_KEY "AIzaSyBuq03f2lsm1lAWrJoGRAmbp9NEDP0Dx48"
#define API_KEY "AIzaSyCvvoxNOc0hjikXHkk3GjeQPMNB8e9N7Uo"

//RealTime Database URL */
//#define DATABASE_URL "https://learningesp8266-1c56d-default-rtdb.europe-west1.firebasedatabase.app/" 
#define DATABASE_URL "https://sommarljusstake-default-rtdb.europe-west1.firebasedatabase.app/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
String sendToMorse;

enum states{
    Disconnected,
    Connected,
    LedsOn,
    LedsOff,
    Morse
};

static states State, NextState;

void setup() {

  int * createMorseArray();
  int * msgToMorse(int * morseArray, char * msgArray);
  char * getMsg();
  char * toLowerCase(char * str);
  void * sendMsg(int * morseMsg, int morseMsgLength);
  int getMorseLength(char * str);
  
  Serial.begin(115200);
  
  wifiSetup();

  firebaseSetup();

  pinMode(5, OUTPUT);    // sets the digital pin 1 as output
  
  State = Disconnected;
  NextState = Disconnected;
}

void wifiSetup(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void firebaseSetup(){
  /* Assign api key*/
  config.api_key = API_KEY;

  /* Assign the RealTime Database URL*/
  config.database_url = DATABASE_URL;

  /* Assign email and password for login*/
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  
  /* Sign up */
  /*if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Connected to firebase");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }*/

  Firebase.begin(&config, &auth);
  
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

/*Sends a float value to connected firebase, assumes that connection to firebase is established*/
void sendFloatToFirebase(char* path, float value){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Write a float value to the database path
    if (Firebase.RTDB.setFloat(&fbdo, path, value)){
      Serial.print("\nFLOAT SENT SUCCESSFULLY");
      Serial.print(" PATH: " + fbdo.dataPath());
      Serial.print(" TYPE: " + fbdo.dataType());
      Serial.print("\n");
    }
    else {
      Serial.println("Sending failed");
      Serial.println("Reason: " + fbdo.errorReason());
    }
  }
  else{
    Serial.println("Couldn't send to firebase");
  }
}

/*gets a float value from assigned path in firebase. Assumes connection to firebase established*/
static float getFloatFromFirebase(char* path){
  
  float floatValue = -1;
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    
     if (Firebase.RTDB.getFloat(&fbdo, path)) {
      if (fbdo.dataType() == "float") {
        floatValue = fbdo.floatData();
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    return floatValue;  
  }
  else {
    return floatValue;
  }
}

/*Sends a boolean value to connected firebase, assumes that connection to firebase is established*/
void sendBoolToFirebase(char* path, bool value){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Write a booelean value to the database path
    if (Firebase.RTDB.setBool(&fbdo, path, value)){
      Serial.print("\nBOOL SENT SUCCESSFULLY");
      Serial.print(" PATH: " + fbdo.dataPath());
      Serial.print(" TYPE: " + fbdo.dataType());
      Serial.print("\n");
    }
    else {
      Serial.println("Sending failed:");
      Serial.println("Reason: " + fbdo.errorReason());
    }
  }
  else{
    Serial.println("Couldn't send to firebase");
  }
}

/*gets a boolean value from assigned path in firebase. Assumes connection to firebase established*/
static bool getBoolFromFirebase(char* path){
  
  bool boolValue = false;
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    
     if (Firebase.RTDB.getBool(&fbdo, path)) {
      if (fbdo.dataType() == "boolean") {
        boolValue = fbdo.boolData ();
      }
    } 
    else {
      Serial.println(fbdo.errorReason());
    }
    return boolValue;  
  }
  else {
    return boolValue;
  }
}

/*Sends a string value to connected firebase, assumes that connection to firebase is established*/
void sendStringToFirebase(char* path, String value){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Write a string value to the database path
    if (Firebase.RTDB.setString(&fbdo, path, value)){
      Serial.print("\nSTRING SENT SUCCESSFULLY");
      Serial.print(" PATH: " + fbdo.dataPath());
      Serial.print(" TYPE: " + fbdo.dataType());
      Serial.print("\n");
    }
    else {
      Serial.println("Sending failed:");
      Serial.println("Reason: " + fbdo.errorReason());
    }
  }
  else{
    Serial.println("Couldn't send to firebase");
  }
}

/*gets a string value from assigned path in firebase. Assumes connection to firebase established*/
static String getStringFromFirebase(char* path){
  
  String stringValue = "-1";
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    
     if (Firebase.RTDB.getString(&fbdo, path)) {
      if (fbdo.dataType() == "string") {
        stringValue = fbdo.stringData();
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    return stringValue;  
  }
  else {
    return stringValue;
  }
}

/*Sends an integer value to connected firebase, assumes that connection to firebase is established*/
void sendIntToFirebase(char* path, int value){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Write a integer value to the database path
    if (Firebase.RTDB.setInt(&fbdo, path, value)){
      Serial.print("\nINTEGER SENT SUCCESSFULLY");
      Serial.print(" PATH: " + fbdo.dataPath());
      Serial.print(" TYPE: " + fbdo.dataType());
      Serial.print("\n");
    }
    else {
      Serial.println("Sending failed:");
      Serial.println("Reason: " + fbdo.errorReason());
    }
  }
  else{
    Serial.println("Couldn't send to firebase");
  }
}

/*gets an integer value from assigned path in firebase. Assumes connection to firebase established*/
static int getIntFromFirebase(char* path){
  
  int intValue = -1;
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    
     if (Firebase.RTDB.getInt(&fbdo, path)) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    return intValue;  
  }
  else {
    return intValue;
  }
}

void lightsOn(int value){
  analogWrite(5, value); 
}

void lightsOff(){
  digitalWrite(5, LOW);
}

char* stringToCharArray (String string){
  char charArray[string.length() + 1];

  for(int i = 0; i < string.length() + 1; i++){
    charArray[i] = string [i];
  }
  return charArray;
}

void * sendMsg(int * morseMsg, int len){
    int count = 0;
    for (size_t i = 0; i < len; i++) {   
        count++;
        if(morseMsg[i] == 0){
            digitalWrite(5, HIGH); //Turn on
            delay(333); 
            digitalWrite(5, LOW);//Turn off
      delay(333);
        } 
        if(morseMsg[i] == 1){
            digitalWrite(5, HIGH); //Turn on
            delay(1000); //wait for 1 sec
            digitalWrite(5, LOW); //Turn off
      delay(333);
        }  
        if(morseMsg[i] == 3){
           delay(1333); 
        }
        if(morseMsg[i] == 2){
           delay(777);//wait for 3 sec
           i = i + 5 - count;
           count = 0;
        }
        if (count == 5){
            delay(777);
            count = 0;
        }  
        
    }
}

char * toLowerCase(char * str){  //This is a place holder depening on how we get msg
     size_t len = strlen(str);
    char *lower;
    for (size_t i = 0; i < len; ++i) {
        lower[i] = tolower((unsigned char)str[i]);
    }
    return lower;
} 
int getMorseLength(char * str){  
    return 5 * strlen(str);;
}
int * msgToMorse(int * morseArray, char * str){  //place holder
    int hold;
    size_t len = strlen(str);
    char* morseMsg;
    for (size_t i = 0; i < len; i++) {
        hold = str[i];        
        if (hold == 32){
            morseMsg[i*5] = 3;
            morseMsg[(i*5)+1] = 2;
            morseMsg[(i*5)+2] = 2;
            morseMsg[(i*5)+3] = 2;
            morseMsg[(i*5)+4] = 2;
        }
        else{
            morseMsg[(i*5)] = morseArray[(hold - 97)*5];
            morseMsg[(i*5)+1] = morseArray[(hold - 97)*5 + 1];
            morseMsg[(i*5)+2] = morseArray[(hold - 97)*5 + 2];
            morseMsg[(i*5)+3] = morseArray[(hold - 97)*5 + 3];
            morseMsg[(i*5)+4] = morseArray[(hold - 97)*5 + 4];
        }
    }
  return morseArray;  
}
int* createMorseArray(){
    static int asciiMorse[200] = {
    0,1,2,2,2, //A
    1,0,0,0,2, //B
    1,0,1,0,2, //C
    1,0,0,2,2, //D
    0,2,2,2,2, //E
    0,0,1,0,2, //F
    1,1,0,2,2, //G
    0,0,0,0,2, //H
    0,0,2,2,2, //I
    0,1,1,1,2, //J
    1,0,1,2,2, //K
    0,1,0,0,2, //L
    1,1,2,2,2, //M
    1,0,2,2,2, //N
    1,1,1,2,2, //O 
    0,1,1,0,2, //P
    1,1,0,1,2, //Q
    0,1,0,2,2, //R
    0,0,0,2,2, //S
    1,2,2,2,2, //T
    0,0,1,2,2, //U
    0,0,0,1,2, //V
    0,1,1,2,2, //W
    1,0,0,1,2, //X
    1,0,1,1,2, //Y
    0,0,1,1,2, //Z
    0,1,1,1,1, //1
    0,0,1,1,1, //2
    0,0,0,1,1, //3
    0,0,0,0,1, //4
    0,0,0,0,0, //5
    1,0,0,0,0, //6
    1,1,0,0,0, //7
    1,1,1,0,0, //8
    1,1,1,1,0, //9
    1,1,1,1,1, //0
    0,1,1,0,1, //Å
    0,1,0,1,2, //Ä
    1,1,1,0,2, //Ö
    1,1,0,1,1};  //this one is a space 
    return asciiMorse;
}

void morseSignal(char* Msg){
    int * morseArray;
    morseArray = createMorseArray();
    char * msgArray;
    msgArray = Msg;
    char * msgLowCase = toLowerCase(msgArray);
    int msgMorseLength = getMorseLength(msgArray);
    int * morseCode;
    morseCode = msgToMorse(morseArray, msgLowCase);
    sendMsg(morseCode, msgMorseLength);
}
void loop() {
    State = NextState;
    int dimVal = getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/dimmer");
    delay(1);
    bool lightStatus = getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/lightStatus");
    delay(1);
    bool morseStatus = getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseStatus");
    delay(1);
    String morseText = getStringFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseText");
    delay(1);
    switch (State){
        case Disconnected:
        Serial.println("Disconnected");
        if(WiFi.status() == WL_CONNECTED){           //if connection with wifi
        NextState = Connected;
        }
        else{
        NextState = Disconnected;
        }
        break;
        case Connected:
            Serial.println("Connected");
            Serial.println(lightStatus);
            Serial.println(dimVal);
            Serial.println(morseStatus);
            Serial.println(morseText);
            if(WiFi.status() != WL_CONNECTED){  //connection lost
                NextState = Disconnected;
            }
            else if(lightStatus){//if on button is pressed
                
                NextState = LedsOn;
            }
            else if(morseStatus){ // Morse
                NextState = Morse;
            }
            else{ //still connected 
                NextState = Connected;
            }
        break;
        case LedsOn:
        Serial.println("LedsOn");
        // turn on the configured pins for the leds
        //go to light on function
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
            else{ //leds still on
                NextState = LedsOn;
            }
        break;
        case LedsOff:
        Serial.println("LedsOff");

        lightsOff();
        NextState = Connected;
        break;
        case Morse:
        Serial.println("Morse");
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
    }
}
