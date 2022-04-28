#include <stdio.h>

int * createMorseArray();
int * msgToMorse(int * morseArray, char * msgArray);
char * getMsg();

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
 
    int * morseCode;
    morseCode = msgToMorse(morseArray, msgArray);
 
    return 0;
}

char * getMsg(){  //This is a place holder depening on how we get msg
    char msg[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    return msg;
}

int * msgToMorse(int * morseArray, char * msgArray){  //place holder

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
    {1,1,1,1,1}
    };
    
    return asciiMorse;
}
