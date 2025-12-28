# This is where i start to build my own expense tracker in C with makefile
# =========================
# Cross-compile Makefile
# Linux / WSL → Windows GUI
# =========================

CC      := x86_64-w64-mingw32-gcc
ASM     := nasm
CFLAGS  := -Wall -Wextra -O2
LDFLAGS := -mwindows

OBJ_DIR := ../build

SRC_C_DIR := ../src
C_SRC   := $(SRC_C_DIR)/main.c
C_OBJ   := $(OBJ_DIR)/main.o

SRC_ASM_DIR := ../AsmSrcGui
ASM_SRC := $(SRC_ASM_DIR)/Gui.asm
ASM_OBJ := $(OBJ_DIR)/Gui.o

TARGET  := ../bin/gui_app.exe

all: $(TARGET)

$(TARGET): $(C_OBJ) $(ASM_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

$(C_OBJ): $(C_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJ): $(ASM_SRC) | $(OBJ_DIR)
	$(ASM) -f win64 $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
