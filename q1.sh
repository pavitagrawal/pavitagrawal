#!/bin/sh

echo "Enter the name of the file to be copied:"
read file_name

if [ ! -f "$file_name" ]; then
    echo "Error: File '$file_name' does not exist."
    exit 1
fi

cp "$file_name" "duplicate_$file_name"
echo "File duplicated as 'duplicate_$file_name'"
