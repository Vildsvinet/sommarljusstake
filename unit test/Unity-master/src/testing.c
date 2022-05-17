#include <stdio.h>
#include "msgToMorseCCode.c"
#include <stdbool.h>
#include "unity.h"
#include "ranLig.c"
void getMsgTest(void)
{
    char * msgArray;
    msgArray = getMsg();
    TEST_ASSERT_TRUE(msgArray == "ABCDEF");
}
void toLowerCaseTest()
{
    char * lower;
    char * str;
    str = "ABCDEF";
    lower = toLowerCase(str);
    TEST_ASSERT_EQUAL_STRING(lower, "abcdef");
}
void getMorseLengthTest(){
    int length;
    length = getMorseLength("ABCDEF");
    TEST_ASSERT_TRUE(length == 30);
}
void msgToMorseTest(){
    int * morseMsg;
    int * morseArrayTable;
    morseArrayTable = createMorseArray();
    morseMsg = msgToMorse(morseArrayTable, "abcdef");
    static int asciiMorse[30] = {0,1,2,2,2,1,0,0,0,2,1,0,1,0,2,1,0,0,2,2,0,2,2,2,2,0,0,1,0,2};
    TEST_ASSERT_CHAR_ARRAY_WITHIN(1,asciiMorse,morseMsg,30);
}
void getDurationTest() {
    int duration;
    duration = getDuration();
    TEST_ASSERT_TRUE(duration == 20);
}
void getRandomNumberTest(){

    int randomNumber = 0;
    int randomNumberAdder;
    double ammountOfRandomCheck;
    ammountOfRandomCheck = 1000;
    for(int i = 0; i < ammountOfRandomCheck; i++){
        randomNumberAdder = getRandomNumber();
        randomNumber = randomNumberAdder + randomNumber;
    }
    double randomNumberAvarage;
    randomNumberAvarage = randomNumber/ammountOfRandomCheck;
    TEST_ASSERT_GREATER_THAN(1, randomNumberAvarage);
    TEST_ASSERT_GREATER_THAN(randomNumberAvarage, 3);
    TEST_ASSERT_TRUE(randomNumberAvarage != 2);
}
void getMsgAntiTest(void)
{
    char * msgArray;
    msgArray = getMsg();
    TEST_ASSERT_FALSE(msgArray == "ABCDE");
}
void toLowerCaseAntiTest()
{
    char * lower;
    char * str;
    str = "ABCDEF";
    lower = toLowerCase(str);
    printf("This should fail");
    TEST_ASSERT_EQUAL_STRING(lower, "abcdef");
}
void getMorseLengthAntiTest(){
    int length;
    length = getMorseLength("ABCDE");
    TEST_ASSERT_FALSE(length == 30);
}
void msgToMorseAntiTest(){
    int * morseMsg;
    int * morseArrayTable;
    morseArrayTable = createMorseArray();
    morseMsg = msgToMorse(morseArrayTable, "qgftj");
    static int asciiMorse[30] = {0,1,2,2,2,1,0,0,0,2,1,0,1,0,2,1,0,0,2,2,0,2,2,2,2,0,0,1,0,2};
    printf("This should fail");
    TEST_ASSERT_CHAR_ARRAY_WITHIN(1,asciiMorse,morseMsg,30);
}
void getDurationAntiTest() {
    int duration;
    duration = getDuration();
    TEST_ASSERT_FALSE(duration == 10);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(getMsgTest);
    RUN_TEST(toLowerCaseTest);
    RUN_TEST(getMorseLengthTest);
    RUN_TEST(msgToMorseTest);
    RUN_TEST(getDurationTest);
    RUN_TEST(getRandomNumberTest);
    RUN_TEST(getMsgAntiTest);
//    RUN_TEST(toLowerCaseAntiTest);
    RUN_TEST(getMorseLengthAntiTest);
   // RUN_TEST(msgToMorseAntiTest);
    RUN_TEST(getDurationAntiTest);
    return UNITY_END();
}