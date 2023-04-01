#!/bin/bash

if [ -f .clang-format ]; then
    FORMAT_FILE=".clang-format"
else
    echo "Error: .clang-format file not found in current directory."
    exit 1
fi

if [ $# -eq 0 ]; then
    echo "Error: no directories specified."
    echo "Usage: $0 <directory1> <directory2> ..."
    exit 1
fi

for dir in "$@"; do
    if [ ! -d "$dir" ]; then
        echo "Error: $dir is not a directory."
        exit 1
    fi
    find "$dir" -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print0 | while IFS= read -r -d '' file; do
        echo "Formatting $file"
        clang-format -i -style=file -fallback-style=none -assume-filename="$FORMAT_FILE" "$file"
    done
done
