#!/bin/bash

AS=77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a
APUB=8520f0098930a754748b7ddcb43ef75a0dbf3a0d26381af4eba4a98eaa9b4e6a
BS=5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb
BPUB=de9edb7d7b7dc1b4d35b61c2ece435373f8343c85b78674dadfc7e146f882b4f
SHARED=4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742

echo "Starting x25519 tests"

COMPUTED_APUB=$(./x25519 $AS | tr -d '\n')
COMPUTED_BPUB=$(./x25519 $BS | tr -d '\n')

COMPUTED_SHARED_A=$(./x25519 $AS $BPUB | tr -d '\n')
COMPUTED_SHARED_B=$(./x25519 $BS $APUB | tr -d '\n')

check_match() {
    if [ "$1" == "$2" ]; then
        echo "PASS: $3"
    else
        echo "FAIL: $3"
        echo "Expected: $2"
        echo "Got:      $1"
        exit 1
    fi
}

check_match "$COMPUTED_APUB" "$APUB" "Alice's public key"
check_match "$COMPUTED_BPUB" "$BPUB" "Bob's public key"
check_match "$COMPUTED_SHARED_A" "$SHARED" "Shared secret (Alice's computation)"
check_match "$COMPUTED_SHARED_B" "$SHARED" "Shared secret (Bob's computation)"

echo "Passed all x25519 tests"
