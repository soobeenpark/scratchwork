#!/bin/bash

for numElems in {1..53}
do
    for iter in {1..3}
    do
        # Run sort
        ./sort "$numElems" >/dev/null
        
        # Check exit condition
        if [ $? -eq 0 ]
        then
            echo "sort with ${numElems} elements (iter ${iter}) success"
        else
            echo "sort with ${numElems} elements (iter ${iter}) ERROR!"
            echo "...exiting"
            exit 1
        fi

    done
done
