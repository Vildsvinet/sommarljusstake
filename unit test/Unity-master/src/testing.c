#include <stdio.h>
#include "msgToMorseCCode.c"
#include <stdbool.h>
#include "unity.h"
void getMsgTest(void)
{
    char * msgArray;
    msgArray = getMsg();
    TEST_ASSERT_TRUE(msgArray == "ABCEF");
}
void toLowerCaseTest()
{
    char * lower;
    char * str;
    str = "ABCDEF";
    lower = toLowerCase(str);
    TEST_ASSERT_TRUE(lower == "abcdef");
}
void getMorseLengthTest(){
    int length;
    length = etMorseLength("ABCDEF");
    TEST_ASSERT_TRUE(length == 30);
}
void msgToMorseTest(){
    int * morseMsg;
    int * morseArrayTable;
    morseArrayTable = createMorseArray();
    morseMsg = msgToMorse(morseArrayTable, "abcdef");
    static int asciiMorse[30] = {0,1,2,2,2,1,0,0,0,2,1,0,1,0,2,1,0,0,2,2,0,2,2,2,2,0,0,1,0,2};
    TEST_ASSERT_TRUE(morseMsg == asciiMorse);
}
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(getMsgTest);
    RUN_TEST(toLowerCaseTest);
    RUN_TEST(getMorseLengthTest);
    RUN_TEST(msgToMorseTest);
    return UNITY_END();
}