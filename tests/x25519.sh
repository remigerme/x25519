#!/bin/bash

echo "Starting x25519 tests"

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

# Tests from section 5
M1=a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4
U1=e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c
OUT1=c3da55379de9c6908e94ea4df28d084f32eccf03491c71f754b4075577a28552

M2=4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d
U2=e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a493
OUT2=95cbde9476e8907d7aade45cb4b873f88b595a68799fa152e6f8f7647aac7957

COMPUTED_OUT1=$(./x25519 $M1 $U1 | tr -d '\n')
COMPUTED_OUT2=$(./x25519 $M2 $U2 | tr -d '\n')

check_match $COMPUTED_OUT1 $OUT1 "First example from section 5"
check_match $COMPUTED_OUT2 $OUT2 "Second example from section 5"

# Tests from section 6

AS=77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a
APUB=8520f0098930a754748b7ddcb43ef75a0dbf3a0d26381af4eba4a98eaa9b4e6a
BS=5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb
BPUB=de9edb7d7b7dc1b4d35b61c2ece435373f8343c85b78674dadfc7e146f882b4f
SHARED=4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742

COMPUTED_APUB=$(./x25519 $AS | tr -d '\n')
COMPUTED_BPUB=$(./x25519 $BS | tr -d '\n')

COMPUTED_SHARED_A=$(./x25519 $AS $BPUB | tr -d '\n')
COMPUTED_SHARED_B=$(./x25519 $BS $APUB | tr -d '\n')

check_match $COMPUTED_APUB $APUB "Alice's public key"
check_match $COMPUTED_BPUB $BPUB "Bob's public key"
check_match $COMPUTED_SHARED_A $SHARED "Shared secret (Alice's computation)"
check_match $COMPUTED_SHARED_B $SHARED "Shared secret (Bob's computation)"

echo "Passed all x25519 tests"
