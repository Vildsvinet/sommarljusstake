#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <sstream>
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
char* sendToMorse;

enum states{
    Disconnected,
    Connected,
    LedsOn,
    LedsOff,
    Morse,
    RandomBlink
};

static states State, NextState;

void setup() {

  int * createMorseArray();
  String msgToMorse(int * morseArray, char * msgArray, size_t len);
  char * getMsg();
  char * toLowerCase(char * str);
  void * sendMsg(String morseMsg, int morseMsgLength);
  int getMorseLength(char * str);
  
  Serial.begin(115200);
  
  wifiSetup();

  firebaseSetup();

  pinMode(5, OUTPUT);    // sets the digital pin 1 as output
  pinMode(4, OUTPUT); 
  pinMode(0, OUTPUT); 
  State = Disconnected;
  NextState = Disconnected;
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
    bool blink = getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/blinkSent");
    delay(1);
    int timer = getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/blinkTimer");
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
            Serial.println(blink);
            Serial.println(timer);
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
            else if(blink){
                NextState = RandomBlink;
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
        sendToMorse = stringToCharArray(morseText);
        morse(morseText);
        //morseSignal(sendToMorse);
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
        Serial.println("randomBlink");
        randomBlink(timer);
        delay(1);   
        sendBoolToFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/blinkSent",false);    
         
        if (lightStatus){
        NextState = LedsOn;
        }
        else if(!lightStatus){ 
            NextState= LedsOff;
        }  
        break;
    }
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
  if(value == 255){
    digitalWrite(5, HIGH); //Turn on
    digitalWrite(4, HIGH);
    digitalWrite(0, HIGH); 
  }
  else{
    analogWrite(5, value); 
    analogWrite(4, value);
    analogWrite(0, value);
  }
}

void lightsOff(){
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
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
    Serial.println(len);
    for (size_t i = 0; i < len; i++) { 
      Serial.println(i);  
        count++;
        int val = morseMsg[i];
        Serial.println(val);
        if(val == 0){
          digitalWrite(5, HIGH); //Turn on
          delay(333); 
          digitalWrite(5, LOW);//Turn off
          delay(333);
        } 
        if(val == 1){
          digitalWrite(5, HIGH); //Turn on
          delay(1000); //wait for 1 sec
          digitalWrite(5, LOW); //Turn off
          delay(333);
        }  
        if(val == 3){
           delay(1333);
        }
        if(val == 2){
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

String msgToMorse(int * morseArray, char * str, size_t len){  //place holder
  Serial.print("msgToMorse1\n");
    char hold;
    Serial.print("msgToMorse2\n");
    int num;
    char* morseMsg;
    Serial.print("msgToMorse3\n");
    for (size_t i = 0; i < len; i++) {
      Serial.print("msgToMorse forLoop\n");
      
        hold = str[i];
        Serial.print("msgToMorse forLoop2\n");
        Serial.println(hold);        
        if (hold == '3'){
          Serial.print("msgToMorse if\n");
            morseMsg[i*5] = 3;
            morseMsg[(i*5)+1] = 2;
            morseMsg[(i*5)+2] = 2;
            morseMsg[(i*5)+3] = 2;
            morseMsg[(i*5)+4] = 2;
        }
        else{
          Serial.print("msgToMorse else\n");
            num = int(hold);

            morseMsg[(i*5)] = morseArray[(num - 97)*5];
            morseMsg[(i*5)+1] = morseArray[(num - 97)*5 + 1];
            morseMsg[(i*5)+2] = morseArray[(num - 97)*5 + 2];
            morseMsg[(i*5)+3] = morseArray[(num - 97)*5 + 3];
            morseMsg[(i*5)+4] = morseArray[(num - 97)*5 + 4];
        }
    }
            int i;
        String s = "";
        for (i = 0; i < len; i++) {
            s = s + morseMsg[i];
        }
        
    
  return s;
    
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
    1,1,1,1,1, //0
    0,1,1,1,1, //1
    0,0,1,1,1, //2
    0,0,0,1,1, //3
    0,0,0,0,1, //4
    0,0,0,0,0, //5
    1,0,0,0,0, //6
    1,1,0,0,0, //7
    1,1,1,0,0, //8
    1,1,1,1,0, //9
    0,1,1,0,1, //Å
    0,1,0,1,2, //Ä
    1,1,1,0,2, //Ö
    3,2,2,2,2};  //this one is a space 
    return asciiMorse;
}

void morseSignal(char* Msg){
    int * morseArray;
    morseArray = createMorseArray();
    char * msgArray;
    msgArray = Msg;
    size_t len = strlen(msgArray);
    char * msgLowCase = toLowerCase(msgArray);
    int msgMorseLength = getMorseLength(msgArray);
    String morseCode;
    //morseCode = stringToMorse(morseArray, msgLowCase, len);
    //sendMsg(morseCode, msgMorseLength);
}

int randomBlink(int duration){
    srand ( time(NULL) );

    int time_spent = 0;


    while(time_spent < duration){

    int randomNumberDuration = getRandomNumber();
    int randomNumberLigth = getRandomNumber();
    turnOnLigths(randomNumberDuration, randomNumberLigth);

    time_spent = time_spent + randomNumberDuration;

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds

    }
    
    return 0;
}

int getRandomNumber(){
    int random_number = rand() % 3 + 1;
    return random_number;
}
void turnOnLigths(int duration, int ligthNumber){

    switch (ligthNumber)
    {
    case 1:
        digitalWrite(5, HIGH); //Turn on
        delay(duration*1000);
        digitalWrite(5, LOW); //Turn off
        break;
    case 2:
        digitalWrite(4, HIGH);
        delay(duration*1000);
        digitalWrite(4, LOW);
        break;
    case 3:
        digitalWrite(0, HIGH);
        delay(duration*1000);
        digitalWrite(0, LOW);
        break;
    default:
        break;
    }

}



void morse(String msg){

  int* morseArray;
  morseArray = createMorseArray();
  int* morseMsg;
  morseMsg = stringToMorse(msg, morseArray);
  //sendMsg(morseMsg, msg.length()*5);
  
}

int* stringToMorse (String Msg, int* morseArray){
  int count;
  int len = Msg.length()*5;
  int morseMsg [len];
  
  for(int i = 0; i < Msg.length(); i++){
    
    int k = i*5;
    //space
    if(int(Msg[i]) == 32){
      count = 195;
      for(int j = 0; j < 5; j++){
        morseMsg[k++] = morseArray[count++];
      } 
    }
    //number
    else if(int(Msg[i]) >= 48 && int(Msg[i]) <= 57){
      count = (int(Msg[i]) - 22)*5;
      for(int j = 0; j < 5; j++){
        morseMsg[k++] = morseArray[count++];
      }
    }
    //upper case
    else if(int(Msg[i]) >= 56 && int(Msg[i]) <= 90){
      count = (int(Msg[i]) - 56)*5;
      for(int j = 0; j < 5; j++){
      morseMsg[k++] = morseArray[count++];
      }
    }
    //lower case
    else{
      count = (int(Msg[i]) - 97)*5;
      for(int j = 0; j < 5; j++){
        morseMsg[k++] = morseArray[count++];
      }
    }
  }  
    count = 0;
    for (size_t i = 0; i < len; i++) {   
        count++;
        int val = morseMsg[i];
        if(val == 0){
            digitalWrite(5, HIGH); //Turn on
            digitalWrite(4, HIGH);
            digitalWrite(0, HIGH);
            delay(333); 
            digitalWrite(5, LOW);//Turn off
            digitalWrite(4, LOW);
            digitalWrite(0, LOW);
            delay(333);
        } 
        if(val == 1){
            digitalWrite(5, HIGH); //Turn on
            digitalWrite(4, HIGH);
            digitalWrite(0, HIGH);
            delay(1000); //wait for 1 sec
            digitalWrite(5, LOW);//Turn off
            digitalWrite(4, LOW);
            digitalWrite(0, LOW);
            delay(333);
        }  
        if(val == 3){
           delay(1333);

        }
        if(val == 2){
           delay(777);//wait for 3 sec
           i = i + 5 - count;
           count = 0;
        }
        if (count == 5){
            delay(777);
            count = 0;
        }    
    }
  return morseMsg;
}
