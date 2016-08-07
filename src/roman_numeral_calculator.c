#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "roman_numeral_calculator.h"

const int decimalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
const char *romanNumerals[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

int valid(char *value) {
  if(strstr(value, "IIII") != NULL || strstr(value, "XXXX") != NULL || strstr(value, "CCCC") != NULL) {
    return 0;
  }
  if(strstr(value, "VV") != NULL || strstr(value, "LL") != NULL || strstr(value, "DD") != NULL) {
    return 0;
  }
  return 1;
}

int starts_with(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) {
     return 1;
   } else {
     return 0;
   }
}

int parse_roman(char *value)
{
  if(!valid(value)) {
    return 0;
  }
  char word2[12];
  int i;
  for(i=0; i<sizeof (romanNumerals) / sizeof *(romanNumerals); i++)
  {
    if(starts_with(value, romanNumerals[i])) {
      int size = strlen(romanNumerals[i]);
      return decimalValues[i] + parse_roman(strcpy(word2,&value[size]));
    }
  }
}

char* convert_to_roman(int decimalValue)
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

char *calculate(char * first, char * second, char operator)
{
  int firstDecimal = parse_roman(first);
  int secondDecimal = parse_roman(second);

  if(!firstDecimal || !secondDecimal) {
    return MESSAGE_INVALID_INPUT;
  }
  switch(operator)
  {
    case OPERATOR_ADD :
      return convert_to_roman(firstDecimal + secondDecimal);
      break;

    case OPERATOR_SUBTRACT :
      if(firstDecimal - secondDecimal < 0) {
        return MESSAGE_INVALID_OPERATION;
      } else {
        return convert_to_roman(firstDecimal - secondDecimal);
      }
      break;
  }
}
