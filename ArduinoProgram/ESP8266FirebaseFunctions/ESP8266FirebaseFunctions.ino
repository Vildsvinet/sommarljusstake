/*
  @brief  This file contains functions for connecting an ESP8266 Wifi module
          to a firebase real time data base. The file also includes tests
          for the functions and has a setup and loop function that runs 
          the tests.
  
  @author Jonathan Gustafson
          jonathgu@kth.se
  
  Parts of the code is inspired by information on:
  https://randomnerdtutorials.com/esp8266-nodemcu-firebase-realtime-database/ 

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

//Network credentials
#define WIFI_SSID "Honor9"
#define WIFI_PASSWORD "1337420blaze"

//User login for firebase
#define USER_EMAIL "valued_customer@sommarljusstake.se"
#define USER_PASSWORD "Secureasfuck123"

//Firebase project API Key
#define API_KEY "AIzaSyCvvoxNOc0hjikXHkk3GjeQPMNB8e9N7Uo"

//RealTime Database URL
#define DATABASE_URL "https://sommarljusstake-default-rtdb.europe-west1.firebasedatabase.app/"

//Define Firebase Data object
FirebaseData fbdo;
//Define Firebase Authentication object
FirebaseAuth auth;
//Define Firebse Configuration object
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

/* 
  -Setup: Starts communication to arduino with baud-rate:115200

  -Connects to wifi

  -Connects to firebase
*/
void setup(){
  
  Serial.begin(115200);
  
  wifiSetup();

  firebaseSetup();
}

/* Main program: Running tests */
void loop(){
  sendAndGetFloatTest();  //testing with Floats
  delay(1000);
  sendAndGetBoolTest();   //testing with Boolean
  delay(1000);
  sendAndGetStringTest(); //testing with Strings
  delay(1000);
  sendAndGetIntTest();    //testing with Integers
  delay(1000);
}

/*Test for send and get float functions*/
void sendAndGetFloatTest(){
  sendFloatToFirebase("tests/testFloat", 0.69 + random(0,100));
  delay(500);
  Serial.println(getFloatFromFirebase("tests/testFloat"));
}

/*Test for send and get bool functions*/
void sendAndGetBoolTest(){
  sendBoolToFirebase("tests/sendBool", true);
  Serial.println(getBoolFromFirebase("tests/testBool"));
  delay(500);
  sendBoolToFirebase("test/sendBool", false);
  Serial.println(getBoolFromFirebase("tests/testBool"));
  delay(500);
}

/*Test for send and get string functions*/
void sendAndGetStringTest(){
  String letters[40] = {"a", "b", "c", "d", "e", "f",
                        "g", "h", "i", "j", "k", "l", 
                        "m", "n", "o", "p", "q", "r", 
                        "s", "t", "u", "v", "w", "x", 
                        "y", "z", "1", "2", "3", "4", 
                        "5", "6", "7", "8", "9", "0"};
                        
  String randomString = "";
  for(int i = 0; i < 10; i++){
    randomString = randomString + letters[random(0,40)];
  }
  
  sendStringToFirebase("tests/testString", randomString);
  Serial.println(getStringFromFirebase("tests/testString"));
}

/*Test for send and get int functions*/
void sendAndGetIntTest(){
  sendIntToFirebase("tests/testInt", random(0, 100));
  delay(500);
  Serial.println(getIntFromFirebase("tests/testInt"));
}

/*Connects arduino to given SSID and Password*/
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

/*
  Connects the arduino to given firebase using given authentication

  Assumes the arduino has network connection
*/
void firebaseSetup(){
  /* Assign api key*/
  config.api_key = API_KEY;

  /* Assign the RealTime Database URL*/
  config.database_url = DATABASE_URL;

  /* Assign email and password for login*/
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

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