#!/bin/bash

K=0900000000000000000000000000000000000000000000000000000000000000
U=0900000000000000000000000000000000000000000000000000000000000000

RESULT=$(./x25519 $K $U)
echo $RESULT

U=$K
K=$RESULT

for ((i = 1; i < 1000; i++)); do
    RESULT=$(./x25519 $K $U)
    
    U=$K
    K=$RESULT

    if [[ "$i" -eq 999 ]]; then
        echo $RESULT
    elif [[ "$i" -eq 999999 ]]; then
        echo $RESULT
    fi
done
