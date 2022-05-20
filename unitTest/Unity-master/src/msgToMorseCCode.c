#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
int * createMorseArray();
int * msgToMorse(int * morseArray, char * msgArray);
char * getMsg();
char * toLowerCase(char * str);
void sendMsg(int * morseMsg, int morseMsgLength);
int getMorseLength(char * str);
int run();


int run(){
    int * morseArray;
    morseArray = createMorseArray();
    char * msgArray;
    msgArray = getMsg();
    char * msgLowCase = toLowerCase(msgArray);
    int msgMorseLength = getMorseLength(msgArray);
    int * morseCode;
    morseCode = msgToMorse(morseArray, msgLowCase);
    sendMsg(morseCode, msgMorseLength);
    return 0;
    
}
void sendMsg(int * morseMsg, int len){
    int count = 0;
    for (size_t i = 0; i < len; i++) {   
        count++;
        if(morseMsg[i] == 0){
            printf("%d", morseMsg[i]); //Turn on
            sleep(1); //wait for 0.5 sec
            printf(" "); //Turn off
			sleep(1);
        } 
        if(morseMsg[i] == 1){
            printf("%d", morseMsg[i]); //Turn on
            sleep(2); //wait for 1 sec
            printf(" "); //Turn off
			sleep(1);
        }  
        if(morseMsg[i] == 2){
           sleep(3);//wait for 3 sec
           i = i + 5 - count;
           count = 0;
        }
        if (count == 5){
            sleep(3);
            count = 0;
        }    
    }
}
char * getMsg(){  //This is a place holder depening on how we get msg
    char *msg = "ABCDEF";
    return msg;
}
char * toLowerCase(char * str){
     size_t len = strlen(str);
    char *lower = calloc(len+1, sizeof(char));
    for (size_t i = 0; i < len; ++i) {
        lower[i] = tolower((unsigned char)str[i]);
    }
    return lower;
} 
int getMorseLength(char * str){  
    return 5 * strlen(str);;
}
int * msgToMorse(int * morseArray, char * str){
    int hold;
    size_t len = strlen(str);
    char *morseMsg = calloc(len+1*5, sizeof(char));
    for (size_t i = 0; i < len; i++) {
        hold = str[i];        
        if (hold == 32){
            morseMsg[i*5] = 1;
            morseMsg[(i*5)+1] = 1;
            morseMsg[(i*5)+2] = 0;
            morseMsg[(i*5)+3] = 1;
            morseMsg[(i*5)+4] = 1;
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
int * createMorseArray(){
    static int asciiMorse[37][5] = {
    {0,1,2,2,2},
    {1,0,0,0,2},
    {1,0,1,0,2},
    {1,0,0,2,2},
    {0,2,2,2,2},
    {0,0,1,0,2},
    {1,1,0,2,2},
    {0,0,0,0,2},
    {0,0,2,2,2},
    {0,1,1,1,2},
    {1,0,1,2,2},
    {0,1,0,0,2},
    {1,1,2,2,2},
    {1,0,2,2,2},
    {1,1,1,2,2},
    {0,1,1,0,2},
    {1,1,0,1,2},
    {0,1,0,2,2},
    {0,0,0,2,2},
    {1,2,2,2,2},
    {0,0,1,2,2},
    {0,0,0,1,2},
    {0,1,1,2,2},
    {1,0,0,1,2},
    {1,0,1,1,2},
    {0,0,1,1,2},
    {0,1,1,1,1},
    {0,0,1,1,1},
    {0,0,0,1,1},
    {0,0,0,0,1},
    {0,0,0,0,0},
    {1,0,0,0,0},
    {1,1,0,0,0},
    {1,1,1,0,0},
    {1,1,1,1,0},
    {1,1,1,1,1},
    {1,1,0,1,1}};  //this one is a space 
    return asciiMorse;
}
