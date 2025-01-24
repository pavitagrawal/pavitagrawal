#!/bin/bash

echo "Enter the names of the files to delete (separated by spaces):"
read -a files_to_delete

if [ ${#files_to_delete[@]} -eq 0 ]; then
    echo "No files entered. Exiting."
    exit 1
fi

echo "Deleting the following files:"

for file in "${files_to_delete[@]}"; do
    echo "$file"
    rm -i "$file"
done

echo "All specified files processed."
