#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

int run();
int getDuration();
int getRandomNumber();
void turnOnLigths(int randomNumberDuration, int randomNumberLigth);

int main(){
//    srand ( time(NULL) );
//    int number = getRandomNumber();
//    printf("%d random s", number);

   run();

    return 0;
}
int run(){
    int duration;
    duration = getDuration();
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
int getDuration(){  //replce with real get
    return 20;
}
int getRandomNumber(){
    int random_number = rand() % 3 + 1;
    return random_number;
}
void turnOnLigths(int duration, int ligthNumber){

    switch (ligthNumber)
    {
    case 1:
        printf("lamp 1 turnd on");
        sleep(duration);
        printf("lamp 1 turneds off");
        break;
    case 2:
        printf("lamp 2 turnd on");
        sleep(duration);
        printf("lamp 2 turned off");
        break;
    case 3:
        printf("lamp 3 turnd on");
        sleep(duration);
        printf("lamp 3 turned off");
        break;
    default:
        break;
    }

}