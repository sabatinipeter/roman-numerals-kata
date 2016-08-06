#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "roman_numeral_calculator.h"

char *calculator_add(char *first, char *second)
{
  int decimalValue = parse_roman(first) + parse_roman(second);
  return convert_to_roman(decimalValue);
}

int parse_roman(char *value)
{
  int decimal = 0;
  int i;
  for(i=0; i<(int)strlen(value); i++)
  {
    switch(value[i]) {
      case 'I' : decimal += 1; break;
      case 'V' : decimal += 5; break;
      case 'X' : decimal += 10; break;
      case 'L' : decimal += 50; break;
      case 'C' : decimal += 100; break;
    }
  }
  if(strstr(value, "IV") != NULL) {
    decimal -= 2;
  }
  return decimal;
}

const char* convert_to_roman(int decimalValue)
{
  char romanNumeral[10] = "";
  while(decimalValue > 0) {
    if(decimalValue-5 >= 0) {
      strcat( romanNumeral, "V");
      decimalValue-= 5;
    } else if (decimalValue-4 >= 0) {
      strcat( romanNumeral, "IV");
      decimalValue-= 4;
    } else {
      strcat( romanNumeral, "I");
      decimalValue-= 1;
    }
  }
  return romanNumeral;
}
