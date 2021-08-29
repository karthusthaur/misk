#! /bin/sh

# export.sh - export data of some programs to ../dat/

set -e

echo "Entering ../dat/"

cd ../dat/

echo "Exporting data"

# Assume build.sh has been executed
fbzs.py
getendian > endian.txt
getlocale > locale.txt
limits    > limits.txt
mts.py    > mts.txt
print.py  > print.txt
waves

echo "Done"