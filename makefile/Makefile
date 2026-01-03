# =========================
# Cross-compile Makefile
# Linux / WSL → Windows GUI
# =========================

CC      := x86_64-w64-mingw32-gcc
ASM     := nasm

# 1. Define where your header files (.h) are located
INC_DIR := ../include

# 2. Add -I$(INC_DIR) so the compiler finds your headers
CFLAGS  := -Wall -Wextra -O2 -I$(INC_DIR)
LDFLAGS := -mwindows

OBJ_DIR := ../build
SRC_C_DIR := ../src

# 3. Automatically find ALL .c files in ../src (not just main.c)
C_SRC   := $(wildcard $(SRC_C_DIR)/*.c)

# Convert .c filenames to .o filenames inside the build folder
C_OBJ   := $(patsubst $(SRC_C_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRC))

SRC_ASM_DIR := ../AsmSrcGui
ASM_SRC := $(SRC_ASM_DIR)/Gui.asm
ASM_OBJ := $(OBJ_DIR)/Gui.o

TARGET  := ../bin/gui_app.exe

all: $(TARGET)

$(TARGET): $(C_OBJ) $(ASM_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# 4. Generic rule to compile ANY .c file found in src
$(OBJ_DIR)/%.o: $(SRC_C_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJ): $(ASM_SRC) | $(OBJ_DIR)
	$(ASM) -f win64 $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean