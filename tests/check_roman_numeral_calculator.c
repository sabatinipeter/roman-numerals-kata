#include <check.h>
#include "../src/roman_numeral_calculator.h"

RomanNumeral* romanNumeral;

void setup(void)
{
  romanNumeral = create_roman_numeral();
}

void teardown(void)
{
  free_roman(romanNumeral);
}

START_TEST(test_add_two_numbers_single_char)
{
  ck_assert_str_eq(calculate(romanNumeral, "I", "I", OPERATOR_ADD), "II");
  ck_assert_str_eq(calculate(romanNumeral, "V", "I", OPERATOR_ADD), "VI");
  ck_assert_str_eq(calculate(romanNumeral, "I", "V", OPERATOR_ADD), "VI");
}
END_TEST

START_TEST(test_add_two_numbers_multi_chars)
{
  ck_assert_str_eq(calculate(romanNumeral, "II", "II", OPERATOR_ADD), "IV");
  ck_assert_str_eq(calculate(romanNumeral, "III", "IV", OPERATOR_ADD), "VII");
  ck_assert_str_eq(calculate(romanNumeral, "X", "XI", OPERATOR_ADD), "XXI");
  ck_assert_str_eq(calculate(romanNumeral, "X", "IX", OPERATOR_ADD), "XIX");
  ck_assert_str_eq(calculate(romanNumeral, "XL", "IX", OPERATOR_ADD), "XLIX");
  ck_assert_str_eq(calculate(romanNumeral, "CM", "CD", OPERATOR_ADD), "MCCC");
  ck_assert_str_eq(calculate(romanNumeral, "CCLIV", "CCCXCIX", OPERATOR_ADD), "DCLIII");
  ck_assert_str_eq(calculate(romanNumeral, "MCDXLIV", "MCMXCIX", OPERATOR_ADD), "MMMCDXLIII");
}
END_TEST

START_TEST(test_add_two_invalid_input)
{
  ck_assert_str_eq(calculate(romanNumeral, "i", "i", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "I", "v", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "I", "s", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "IIII", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "XXXX", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "CCCC", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "VV", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "LL", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "DD", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "IVI", "V", OPERATOR_ADD), MESSAGE_INVALID_INPUT);
  ck_assert_str_eq(calculate(romanNumeral, "MMMM", "I", OPERATOR_SUBTRACT), MESSAGE_INVALID_INPUT);
}
END_TEST

START_TEST(test_subtract_number_from_another)
{
  ck_assert_str_eq(calculate(romanNumeral, "V", "I", OPERATOR_SUBTRACT), "IV");
  ck_assert_str_eq(calculate(romanNumeral, "M", "II", OPERATOR_SUBTRACT), "CMXCVIII");
  ck_assert_str_eq(calculate(romanNumeral, "I", "V", OPERATOR_SUBTRACT), MESSAGE_INVALID_OPERATION);
  ck_assert_str_eq(calculate(romanNumeral, "V", "X", OPERATOR_SUBTRACT), MESSAGE_INVALID_OPERATION);
  ck_assert_str_eq(calculate(romanNumeral, "I", "I", OPERATOR_SUBTRACT), MESSAGE_INVALID_OPERATION);
  ck_assert_str_eq(calculate(romanNumeral, "MMMCMXCIX", "MMMCMXCIX", OPERATOR_ADD), MESSAGE_INVALID_OPERATION);
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
