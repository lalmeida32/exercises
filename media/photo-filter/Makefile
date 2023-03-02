CC := gcc
CFLAGS := -Wall -Wextra -Werror

SRC_DIR := src
TMP_DIR := tmp
OUT_FILE := out
MAIN_FILE := main

C_FILES := $(shell find . -wholename './$(SRC_DIR)/*.c')
TMP_FILES := $(shell find . -wholename './$(TMP_DIR)/*')
BIN_FILES := $(shell find . -wholename './*.bin') 

all:
	$(CC) $(CFLAGS) -o $(OUT_FILE).bin $(C_FILES)

clean:
	rm -rf $(TMP_FILES) $(BIN_FILES)

run:
	./$(OUT_FILE).bin

valgrind:
	valgrind ./$(OUT_FILE).bin