#!/bin/bash

output_file="output.txt"

# Clear the output file at the start
> "$output_file"

# Number of iterations (adjust as needed)
iterations=1000
echo "Iterating through $iterations games"

for ((i = 1; i <= iterations; i++)); do
    # Run the program and capture the output
    final_line=$(./main.exe | tail -n 1)
    
    # Append the final line to the output file
    echo "$final_line" >> "$output_file"
done

grep output.txt -oe "Team [0-9].*" | sort | uniq -c
