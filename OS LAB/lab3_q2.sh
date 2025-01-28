#!/bin/bash

# Ask the user to enter the directory path
echo "Enter the directory path where you want to search:"
read dir_path

# Ask the user to enter the pattern (string) to search for
echo "Enter the pattern (string) to search for in file names:"
read pattern

# Check if the directory exists
if [ -d "$dir_path" ]; then
    # List all files in the directory containing the input pattern
    echo "Files containing the pattern '$pattern' in their names:"
    find "$dir_path" -type f -name "*$pattern*" -exec basename {} \;
else
    echo "The directory '$dir_path' does not exist."
fi
