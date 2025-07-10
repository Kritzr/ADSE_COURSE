#!/bin/bash

TMP_FILE="/tmp/shared_input.txt"

echo "Enter something:"
read user_input

echo "$user_input" > "$TMP_FILE"

echo "[P1] INPUT SAVED. Run P2 to see the results"
