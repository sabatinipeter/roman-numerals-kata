#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "roman_numeral_calculator.h"

static const int decimalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
static const char *romanNumerals[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

char *calculator_add(char *first, char *second)
{
  int decimalValue = parse_roman(first) + parse_roman(second);
  // printf("START=================================\nDECIMAL VALUE = %d\n", decimalValue);
  char *romanValue = convert_to_roman(decimalValue);
  // printf("ROMAN VALUE = %s\n", romanValue);
  // printf("END=================================\n\n", romanValue);
  return romanValue;
}

int parse_roman(char *value)
{
  int decimal = 0;
  int i;
  for(i=0; i<(int)strlen(value); i++)
  {
    switch(value[i])
    {
      case 'I' : decimal += 1; break;
      case 'V' : decimal += 5; break;
      case 'X' : decimal += 10; break;
      case 'L' : decimal += 50; break;
      case 'C' : decimal += 100; break;
      case 'D' : decimal += 500; break;
      case 'M' : decimal += 1000; break;
    }
  }
  if(strstr(value, "IV") != NULL || strstr(value, "IX") != NULL)
  {
    decimal -= 2;
  }
  if(strstr(value, "XL") != NULL || strstr(value, "XC") != NULL)
  {
    decimal -= 20;
  }
  if(strstr(value, "CD") != NULL || strstr(value, "CM") != NULL)
  {
    decimal -= 200;
  }
  return decimal;
}

const char* convert_to_roman(int decimalValue)
{
  char romanNumeral[10] = "";

  int i;
  for(i=0; i<sizeof (decimalValues) / sizeof *(decimalValues); i++)
  {
    while(decimalValue - decimalValues[i] >= 0)
    {
      strcat( romanNumeral, romanNumerals[i]);
      decimalValue-= decimalValues[i];
    }
  }

  return romanNumeral;
}
