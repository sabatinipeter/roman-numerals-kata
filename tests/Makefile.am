## Process this file with automake to produce Makefile.in

TESTS = check_roman_numeral_calculator
check_PROGRAMS = check_roman_numeral_calculator
check_roman_numeral_calculator_SOURCES = check_roman_numeral_calculator.c $(top_builddir)/src/roman_numeral_calculator.h
check_roman_numeral_calculator_CFLAGS = @CHECK_CFLAGS@
check_roman_numeral_calculator_LDADD = $(top_builddir)/src/libroman_numeral_calculator.la @CHECK_LIBS@
