#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <root_directory> [<exclude_directory1> ...]"
  exit 1
fi

if [ -n "${@:2}" ]; then
  FILES=$(find "$1" -type d \( -name "${@:2}" -prune \) -o -type f \( -name "*.cpp" -o -name "*.h" \) -print)
else
  FILES=$(find "$1" -type f \( -name "*.cpp" -o -name "*.h" \))
fi


for file in $FILES; do
  echo "Formatting file: $file"
  clang-format -i -style=file "$file"
done