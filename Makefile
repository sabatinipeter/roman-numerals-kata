# the compiler: gcc for C program
CC = gcc

# compiler flags:
CFLAGS := -g -Wall -Werror -std=c99
OBJS := $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
OBJS_TEST := $(patsubst tests/%.c, tests/%.o,$(wildcard tests/*.c))
LIBS := `pkg-config --libs check`

# the build target executable:
TARGET = roman_numeral_calculator
BUILD_DIR = build

all: $(OBJS) $(OBJS_TEST)
		@mkdir -p $(BUILD_DIR)
		$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(TARGET) $(OBJS) $(OBJS_TEST) $(LIBS)

test:
	@$(BUILD_DIR)/$(TARGET)
.PHONY : test

clean:
	$(RM) -r src/*.o tests/*.o $(BUILD_DIR)
.PHONY : clean
