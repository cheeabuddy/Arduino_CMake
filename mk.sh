#! /bin/bash

echo "Hi $USER"

cd bin/simulation
make

PRG=$(find . -name simulation.bin)

echo Found program in $PRG

$PRG