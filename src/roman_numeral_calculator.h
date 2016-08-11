#ifndef ROMAN_NUMERAL_CALCULATOR_H
#define ROMAN_NUMERAL_CALCULATOR_H

#define MAX_VALUE 3999

#define OPERATOR_ADD '+'
#define OPERATOR_SUBTRACT '-'

#define MESSAGE_INVALID_INPUT "INVALID INPUT"
#define MESSAGE_INVALID_OPERATION "INVALID OPERATION"

typedef struct RomanNumeral RomanNumeral;

RomanNumeral* create_roman_numeral();

void free_roman(RomanNumeral* m);

char* calculate(RomanNumeral* m, char first[], char second[], char operator);

#endif /* ROMAN_NUMERAL_CALCULATOR_H */
