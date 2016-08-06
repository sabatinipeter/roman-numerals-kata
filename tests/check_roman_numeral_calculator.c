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
  ck_assert_str_eq(calculator_add("I", "I"), "II");

  ck_assert_str_eq(calculator_add("V", "I"), "VI");
  ck_assert_str_eq(calculator_add("I", "V"), "VI");
}
END_TEST

START_TEST(test_add_two_numbers_multi_chars)
{
  ck_assert_str_eq(calculator_add("II", "II"), "IV");
  ck_assert_str_eq(calculator_add("III", "IV"), "VII");
  ck_assert_str_eq(calculator_add("X", "XI"), "XXI");
  ck_assert_str_eq(calculator_add("X", "IX"), "XIX");
  ck_assert_str_eq(calculator_add("XL", "IX"), "XLIX");
  ck_assert_str_eq(calculator_add("CM", "CD"), "MCCC");
  ck_assert_str_eq(calculator_add("CCLIV", "CCCXCIX"), "DCLIII");

}
END_TEST


Suite * roman_numeral_calculator_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Roman Numeral Calculator");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_add_two_numbers_single_char);
    tcase_add_test(tc_core, test_add_two_numbers_multi_chars);
    suite_add_tcase(s, tc_core);

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
