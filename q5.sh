#!/bin/bash

echo "Enter the patterns to search for (separated by spaces):"
read -a patterns

echo "Enter the input file name:"
read input_file

if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' does not exist."
    exit 1
fi

while true; do
    echo "a. Search the patterns in the given input file."
    echo "b. Delete all occurrences of the patterns in the given input file."
    echo "c. Exit"

    read -p "Enter your choice (a/b/c): " choice

    case "$choice" in
        a)
            echo "Searching patterns in '$input_file':"
            for pattern in "${patterns[@]}"; do
                echo "Pattern: '$pattern'"
                grep "$pattern" "$input_file"
            done
            ;;
        b)
            echo "Deleting occurrences of patterns in '$input_file':"
            for pattern in "${patterns[@]}"; do
                sed -i "s/$pattern//g" "$input_file"
            done
            echo "Occurrences deleted."
            ;;
        c)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter 'a', 'b', or 'c'."
            ;;
    esac
done
