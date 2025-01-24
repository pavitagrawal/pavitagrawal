#!/bin/bash

echo "Enter the option (-linecount, -wordcount, -charcount):"
read option

echo "Enter the file name:"
read file

if [ ! -f "$file" ]; then
    echo "Error: File '$file' does not exist."
    exit 1
fi

case "$option" in  
    -linecount)
        result=$(wc -l < "$file")
        echo "Line count in '$file': $result"
        ;;
    -wordcount)
        result=$(wc -w < "$file")
        echo "Word count in '$file': $result"
        ;;
    -charcount)
        result=$(wc -c < "$file")
        echo "Character count in '$file': $result"
        ;;
    *)
        echo "Invalid option. Please use -linecount, -wordcount, or -charcount."
        exit 1
        ;;
esac
