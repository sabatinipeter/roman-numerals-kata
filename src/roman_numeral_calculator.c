#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "roman_numeral_calculator.h"

static const int decimalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
static const char *romanNumerals[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

char *calculator_add(char *first, char *second)
{
  int f = parse_roman(first);
  int s = parse_roman(second);

  if(!f || !s) {
    return "INVALID INPUT";
  }

  return convert_to_roman(f + s);
}

char *calculator_subtract(char *first, char *second)
{
  int f = parse_roman(first);
  int s = parse_roman(second);

  if(!f || !s) {
    return "INVALID INPUT";
  }

  return convert_to_roman(f - s);
}

int valid(char *value) {
  if(strstr(value, "IIII") != NULL || strstr(value, "XXXX") != NULL || strstr(value, "CCCC") != NULL) {
    return 0;
  }
  if(strstr(value, "VV") != NULL || strstr(value, "LL") != NULL || strstr(value, "DD") != NULL) {
    return 0;
  }
  return 1;
}

int parse_roman(char *value)
{
  if(!valid(value)) {
    return 0;
  }
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
      default : return 0; break;
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
  char romanNumeral[12] = "";

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
