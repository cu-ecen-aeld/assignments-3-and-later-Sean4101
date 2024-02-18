#!/bin/sh

writefile=$1
writestr=$2

if [ $# -eq 0 ]; then
    echo "writefile is not specified!"
    exit 1
elif [ $# -eq 1 ]; then
    echo "writestr is not specified!"
    exit 1
fi

mkdir -p "$(dirname "$writefile")"

echo "$writestr" > "$writefile"

if [ $? -ne 0 ]; then
    echo "Could not create the file $writefile."
    exit 1
fi

exit 0