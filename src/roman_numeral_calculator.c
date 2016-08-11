#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "roman_numeral_calculator.h"

const int decimalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
const char *romanNumerals[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
const char validRegex[] = "^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$";

struct RomanNumeral
{
    char value[12];
};

regex_t regex;

int valid(char value[]) {
  int reti = regcomp(&regex, validRegex, REG_EXTENDED);
  if (reti) {
      exit(1);
  }
  reti = regexec(&regex, value, 0, NULL, 0);
  if (!reti) {
      return 1;
  }
  else if (reti == REG_NOMATCH) {
      return 0;
  }
}

int starts_with(const char a[], const char b[])
{
   if(strncmp(a, b, strlen(b)) == 0) {
     return 1;
   } else {
     return 0;
   }
}

int parse_roman(char value[])
{
  if(!valid(value)) {
    return 0;
  }
  int i;
  for(i=0; i<sizeof (romanNumerals) / sizeof *(romanNumerals); i++)
  {
    if(starts_with(value, romanNumerals[i])) {
      int size = strlen(romanNumerals[i]);
      char string[12];
      return decimalValues[i] + parse_roman(strcpy(string,&value[size]));
    }
  }
}

void convert_to_roman(RomanNumeral* m, int decimalValue)
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
  strcpy(m->value, romanNumeral);
}

RomanNumeral* create_roman_numeral(){
  RomanNumeral* m;

  m = malloc(sizeof(RomanNumeral));

  if (m == NULL)
  {
      return NULL;
  }
  return m;
}

void free_roman(RomanNumeral* m) {
  free(m);
  return;
}

char* calculate(RomanNumeral* m, char first[], char second[], char operator)
{
  int firstDecimal = parse_roman(first);
  int secondDecimal = parse_roman(second);

  if(!firstDecimal || !secondDecimal) {
    strcpy(m->value, MESSAGE_INVALID_INPUT);
    return m->value;
  }
  int decimalToConvert;
  int condition;
  switch(operator)
  {
    case OPERATOR_ADD :
      decimalToConvert = firstDecimal + secondDecimal;
      condition = decimalToConvert > MAX_VALUE;
      break;

    case OPERATOR_SUBTRACT :
      decimalToConvert = firstDecimal - secondDecimal;
      condition = decimalToConvert <= 0;
      break;
  }
  if(condition) {
    strcpy(m->value, MESSAGE_INVALID_OPERATION);
  } else {
    convert_to_roman(m, decimalToConvert);
  }
  return m->value;
}
