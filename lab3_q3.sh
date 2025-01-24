#!/bin/bash

echo "Enter the file name pattern to search for (e.g., '*.txt'):"
read pattern

echo "Script started."

find . -type f -name "$pattern" | while IFS= read -r file; do
    new_name="${file%.txt}.text"

    echo "Processing file: '$file'"
    echo "New name will be: '$new_name'"

    if [ -e "$new_name" ]; then
        echo "Error: '$new_name' already exists. Skipping '$file'."
        continue
    fi

    mv "$file" "$new_name"

    if [ $? -eq 0 ]; then
        echo "Renamed: '$file' to '$new_name'"
    else
        echo "Failed to rename '$file'. Permission denied or other error."
    fi
done
echo "Script finished."
