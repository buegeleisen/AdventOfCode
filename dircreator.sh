#!/bin/bash

echo "Creating dir for day" $1
day=$1

mkdir "src/day"$day
touch "src/day"$day"/input"
touch "src/day"$day"/input_test"
touch "src/day"$day"/main.cpp"
