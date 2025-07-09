#!/bin/bash

read -p "enter path to the first  directory: " dir1
read -p "enter path to the second directory: " dir2

if[[! -d ["dir1"]]; then 
    echo "Error: '$dir1' is not valid"
    exit 1
fi 

if[[! -d ["dir2"]]; then  
    echo "Error: '$dir2' is not valid" 
    exit 1 
fi 

file1 = $(ls -l "$dir1"|sort)
file2 = $(ls -l "$dir2"|sort)



