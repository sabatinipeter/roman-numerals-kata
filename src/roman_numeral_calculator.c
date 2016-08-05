#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "roman_numeral_calculator.h"

char *calculator_add(char *first, char *second)
{
  char dest[10];
  strcpy( dest, first );
  strcat( dest, second );
  return dest;
}
