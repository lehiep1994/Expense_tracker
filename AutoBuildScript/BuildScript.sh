#!/usr/bin/env bash

set -e  # Exit on error

NOW=$(date '+%Y-%m-%d %H:%M:%S')

# Absolute path of this script
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Project root (one level above scripts/)
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

# Paths
MAKEFILE_PATH="$ROOT_DIR/makefile/Makefile"
BIN_DIR="$ROOT_DIR/bin"
BIN_NAME="gui_app.exe"
BIN_PATH="$BIN_DIR/$BIN_NAME"

# Clean previous build
echo "[INFO $NOW] Cleaning previous build..."
make -f "$MAKEFILE_PATH" clean >> /dev/null 2>&1 || true
rm ../build/*.o >> /dev/null 2>&1 || true

# Build
echo "[INFO $NOW] Building using Makefile..."
make -f "$MAKEFILE_PATH" >> /dev/null 2>&1

# Run
if [[ ! -x "$BIN_PATH" ]]; then
    echo "[ERROR $NOW] Binary not found or not executable: $BIN_PATH"
    exit 1
fi

echo "[INFO $NOW] Running $BIN_NAME..."
"$BIN_PATH"
