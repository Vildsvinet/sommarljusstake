#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int * createMorseArray();
int * msgToMorse(int * morseArray, char * msgArray, int msgLength);

char * getMsg();
char * toLowerCase(char * str);

/*void morseToBlink(){

}*/

/*void stringToMorse(char* c, int length){
    while (c++ <= length){
        
    }
}*/

int main(){

     int * morseArray;
    morseArray = createMorseArray();
    
    char * msgArray;
    msgArray = getMsg();
    int msgLength = 6; //this needs to be not hard coded
 
    char * msgLowCase = toLowerCase(msgArray);
    
 
    int * morseCode;
    morseCode = msgToMorse(morseArray, msgLowCase, msgLength);
 
 
    return 0;
}

char * getMsg(){  //This is a place holder depening on how we get msg
    char *msg = "ABCDE";
    return msg;
}


char * toLowerCase(char * str){  //This is a place holder depening on how we get msg
     size_t len = strlen(str);
    char *lower = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; ++i) {
        lower[i] = tolower((unsigned char)str[i]);
    }
     
    return lower;
} 


int * msgToMorse(int * morseArray, char * str, int msgLength){  //place holder

   
  
  
    int hold;
    size_t len = strlen(str);
    char *morseMsg = calloc(len+1*5, sizeof(char));
    printf("%s \n", str);

    for (size_t i = 0; i < len; i++) {
        hold = str[i];
        printf("%d \n", hold);
        
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
    
    for (int i = 0; i < 25; i++){
        printf("%d ", morseMsg[i]);
        
    }
    
    printf("test 1");
  
  
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
