#! /bin/bash

echo "Hi $USER"

PRG=$(find . -name $1)

echo Found program in $PRG

$PRG