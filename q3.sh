#!/bin/bash

selection_sort() {
    local arr=("$@")
    local n=${#arr[@]}

    for ((i=0; i < n-1; i++)); do
        min=$i
        for ((j=i+1; j < n; j++)); do
            if [[ "${arr[j]}" < "${arr[min]}" ]]; then
                min=$j
            fi
        done

        temp="${arr[min]}"
        arr[min]="${arr[i]}"
        arr[i]="$temp"
    done

    echo "Sorted strings:"
    for element in "${arr[@]}"; do
        echo "\"$element\""
    done
}

echo "Enter strings to sort (separated by spaces):"
read -a user_input

selection_sort "${user_input[@]}"
