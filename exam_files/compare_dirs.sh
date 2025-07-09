#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory1> <directory2>"
    exit 1
fi

DIR1="$1"
DIR2="$2"

if [ ! -d "$DIR1" ] || [ ! -d "$DIR2" ]; then
    echo "Both arguments must be valid directories."
    exit 1
fi

FILES1=$(ls "$DIR1" 2>/dev/null | sort)
FILES2=$(ls "$DIR2" 2>/dev/null | sort)


TMP1=$(mktemp)
TMP2=$(mktemp)

echo "$FILES1" > "$TMP1"
echo "$FILES2" > "$TMP2"

echo "Common files:"
comm -12 "$TMP1" "$TMP2"
echo

echo "Files only in $DIR1:"
comm -23 "$TMP1" "$TMP2"
echo

echo "Files only in $DIR2:"
comm -13 "$TMP1" "$TMP2"

rm "$TMP1" "$TMP2"

