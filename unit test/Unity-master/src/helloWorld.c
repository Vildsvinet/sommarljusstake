#include <stdio.h>
#include "msgToMorseCCode.c"
#include <stdbool.h>
#include "unity.h"
void test_true_should_be_true(void)
{
    TEST_ASSERT_TRUE(true);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_true_should_be_true);
    return UNITY_END();
}