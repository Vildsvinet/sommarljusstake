#include "msgToMorseCCode.c"
#include <stdbool.h>
#include "unity.h"
void test_true_should_be_true(void)
{
    TEST_ASSERT_TRUE(true);
}
void test_true_should_be_true_anti(void)
{
    TEST_ASSERT_FALSE(false);
}
void test_true_should_be_false(void)
{
    TEST_ASSERT_TRUE(false);
}
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_true_should_be_true);
    RUN_TEST(test_true_should_be_true_anti);
    RUN_TEST(test_true_should_be_false);
    return UNITY_END();
}