#!/bin/bash

# Name of the C file (change if your file name is different)
SOURCE_FILE="eigenvalues.c"

# Output executable file name
OUTPUT_FILE="eigenvalues"

# Compile with math and complex libraries
gcc "$SOURCE_FILE" -o "$OUTPUT_FILE" -lm -Wall -std=c11

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful! Run ./$OUTPUT_FILE to execute."
else
    echo "Compilation failed."
fi

