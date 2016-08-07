#include <check.h>
#include "../src/roman_numeral_calculator.h"

void setup(void)
{
}

void teardown(void)
{
}

START_TEST(test_add_two_numbers_single_char)
{
  ck_assert_str_eq(calculate("I", "I", OPERATOR_ADD), "II");
  ck_assert_str_eq(calculate("V", "I", OPERATOR_ADD), "VI");
  ck_assert_str_eq(calculate("I", "V", OPERATOR_ADD), "VI");
}
END_TEST

START_TEST(test_add_two_numbers_multi_chars)
{
  ck_assert_str_eq(calculate("II", "II", OPERATOR_ADD), "IV");
  ck_assert_str_eq(calculate("III", "IV", OPERATOR_ADD), "VII");
  ck_assert_str_eq(calculate("X", "XI", OPERATOR_ADD), "XXI");
  ck_assert_str_eq(calculate("X", "IX", OPERATOR_ADD), "XIX");
  ck_assert_str_eq(calculate("XL", "IX", OPERATOR_ADD), "XLIX");
  ck_assert_str_eq(calculate("CM", "CD", OPERATOR_ADD), "MCCC");
  ck_assert_str_eq(calculate("CCLIV", "CCCXCIX", OPERATOR_ADD), "DCLIII");
  ck_assert_str_eq(calculate("MCDXLIV", "MCMXCIX", OPERATOR_ADD), "MMMCDXLIII");
  // ck_assert_str_eq(calculate("MMMCMXCIX", "MMMCMXCIX", OPERATOR_ADD), "MESSAGE INVALID OPERATION");
}
END_TEST

START_TEST(test_add_two_invalid_input)
{
  ck_assert_str_eq(calculate("i", "i", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("I", "v", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("I", "s", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("IIII", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("XXXX", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("CCCC", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("VV", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("LL", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("DD", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate("IVI", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
}
END_TEST

START_TEST(test_subtract_number_from_another)
{
  ck_assert_str_eq(calculate("V", "I", OPERATOR_SUBTRACT), "IV");
  ck_assert_str_eq(calculate("M", "II", OPERATOR_SUBTRACT), "CMXCVIII");
  ck_assert_str_eq(calculate("I", "V", OPERATOR_SUBTRACT), MESSAGE_INVALID_OPERATION);
  ck_assert_str_eq(calculate("V", "X", OPERATOR_SUBTRACT), MESSAGE_INVALID_OPERATION);
}
END_TEST

Suite * roman_numeral_calculator_suite(void)
{
    Suite *s;
    TCase *tc_core;

    TCase *tc_core_2;

    s = suite_create("Roman Numeral Calculator");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_add_two_numbers_single_char);
    tcase_add_test(tc_core, test_add_two_numbers_multi_chars);
    suite_add_tcase(s, tc_core);

    tc_core_2 = tcase_create("Core2");

    tcase_add_checked_fixture(tc_core_2, setup, teardown);
    tcase_add_test(tc_core_2, test_add_two_invalid_input);
    tcase_add_test(tc_core_2, test_subtract_number_from_another);
    suite_add_tcase(s, tc_core_2);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = roman_numeral_calculator_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
