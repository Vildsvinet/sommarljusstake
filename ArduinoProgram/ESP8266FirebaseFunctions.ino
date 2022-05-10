/*
  @brief  This file contains functions for 
  
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

void setup(){
  
  Serial.begin(115200);
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

void loop(){


  Serial.println(getIntFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/dimmer"));
  delay(1000);
  Serial.println(getBoolFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/lightStatus"));
  delay(1000);
  Serial.println(getStringFromFirebase("users/xfgWcU9o3decIkhbWSLkaU5acIl1/morseText"));
  delay(1000);
  Serial.print("Firebase authentication: ");
  Serial.print(Firebase.authenticated());
  Serial.print("\n");
  delay(1000);
  /*sendAndGetFloatTest();
  delay(1000);
  sendAndGetBoolTest();
  delay(1000);
  sendAndGetStringTest();
  delay(1000);
  sendAndGetIntTest();
  delay(1000);*/
  
}

/*Test for send and get float functions*/
void sendAndGetFloatTest(){
  sendFloatToFirebase("test/sendFloat", 0.69 + random(0,100));
  Serial.println(getFloatFromFirebase("test/getFloat"));
}

void sendAndGetBoolTest(){
  sendBoolToFirebase("test/sendBool", true);
  Serial.println(getBoolFromFirebase("test/getBool"));
}

void sendAndGetStringTest(){
  sendStringToFirebase("test/sendString", "ti ezalb");
  Serial.println(getStringFromFirebase("test/getString"));
}

void sendAndGetIntTest(){
  sendIntToFirebase("test/sendInt", 024);
  Serial.println(getIntFromFirebase("test/getInt"));
}

/*Sends a float value to connected firebase, assumes that connection to firebase is established*/
void sendFloatToFirebase(char* path, float value){
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
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
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
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
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
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
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    
     if (Firebase.RTDB.getBool(&fbdo, path)) {
      if (fbdo.dataType() == "bool") {
        boolValue = fbdo.boolData();
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
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
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
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
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
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
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
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
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
