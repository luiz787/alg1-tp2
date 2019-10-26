#!/bin/bash

cd ../../

rm -r experimental_output
mkdir -p experimental_output

make clean
make

for iter in {1..100..1}; do
    for size in {100..1000..100}; do
        echo "Running program for input size $size, iteration $iter."
        input="tests/test_cases/experimental_analysis/in/${size}.in"
        output="experimental_output/${size}.out"
        ./bin/tp2 $input >> $output
        echo "Done..."
    done
done

make clean

