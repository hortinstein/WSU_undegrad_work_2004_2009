#!/bin/bash

# CptS 425/580 Demo Script for Program #1 -- Caesar Cipher
# Revised:  14 February 2009, by AD McKinnon

echo "CptS 425/580 Program #1 Demo Script"

if [ $# -lt 1 ]
then
    echo "Usage:  demo.sh cpts425p1[LASTNAME]"
    exit
fi

rm -Rf $1_demo
mkdir $1_demo
cd $1_demo
cp ../demo.txt .

tar -xzf ../$1.tar.gz
make

echo "Program #1 Demo Script"
./caesarCipher -i demo.txt -k 42 -o demo.cipher

echo " "
echo "****** Caesar Cipher comparison *****"
diff -s demo.cipher ../demo.cipher | head
echo "*************************************"

./charFreqGen -i demo.txt -o demo.freq

./caesarAttack -c demo.cipher -f demo.freq -p phi.txt -o demo.plain

echo " "
echo "****** Caesar Attack comparison *****"
diff -s demo.plain ../demo.txt | head
echo "*************************************"

cd ..
