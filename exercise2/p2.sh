#!/bin/bash

TMP_FILE="/tmp/shared_input.txt"

if [ -f "$TMP_FILE" ]; then
    echo "[P2] Input from P1:"
    cat "$TMP_FILE"
else
    echo "[P2] No input found from P1"
fi
