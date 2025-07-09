#!/bin/bash

#we get the user iinput
read -p "Enter calculation (e.g. 10 + 5): " num1 op num2

# using a regex to see if the given input numbers are valid ints or not  (also float)
if ! [[ "$num1" =~ ^-?[0-9]+([.][0-9]+)?$ ]] || ! [[ "$num2" =~ ^-?[0-9]+([.][0-9]+)?$ ]]; then
  echo "Error: Invalid number(s)."
  exit 1
fi
#actual operation
case "$op" in
  +) result=$(echo "$num1 + $num2" | bc) ;;
  -) result=$(echo "$num1 - $num2" | bc) ;;
  \*) result=$(echo "$num1 * $num2" | bc) ;;  
  /) 
    if [ "$num2" == "0" ]; then
      echo "Error: Division by zero."
      exit 1
    fi
    result=$(echo "scale=2; $num1 / $num2" | bc)
    ;;
  *)
    echo "Error: Unsupported operator. Use +, -, *, or /"
    exit 1
    ;;
esac

echo "Result: $result"
