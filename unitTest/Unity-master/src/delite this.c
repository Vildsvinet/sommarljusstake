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
            digitalWrite(4, HIGH);
            digitalWrite(0, HIGH);
            delay(333);
            digitalWrite(5, LOW);//Turn off
            digitalWrite(4, LOW);
            digitalWrite(0, LOW);
            delay(333);
        }
        if(morseMsg[i] == 1){
            digitalWrite(5, HIGH); //Turn on
            digitalWrite(4, HIGH);
            digitalWrite(0, HIGH);
            delay(1000); //wait for 1 sec
            digitalWrite(5, LOW); //Turn off
            digitalWrite(4, LOW);
            digitalWrite(0, LOW);
            delay(333);
        }
        if(morseMsg[i] == 3){
            delay(10000);
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
int * msgToMorse(int * morseArray, char * str){
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