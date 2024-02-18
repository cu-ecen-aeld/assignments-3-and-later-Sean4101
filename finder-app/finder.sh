#!/bin/sh

filesdir=$1
searchstr=$2

if [ $# -eq 0 ]; then
    echo "filesdir is not specified!"
    exit 1
elif [ $# -eq 1 ]; then
    echo "searchstr is not specified!"
    exit 1
fi

if [ ! -d "$filesdir" ]; then
    echo "'$filesdir' is not a valid directory!"
    exit 1
fi

file_count=$(find "$filesdir" -type f | wc -l)
matching_file_count=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $file_count and the number of matching lines are $matching_file_count"
exit 0