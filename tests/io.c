#include "montgomery_io.h"

#include <assert.h>
#include <gmp.h>
#include <stdio.h>

void check_scalar(char *in, mpz_t expected) {
    mpz_t computed;
    mpz_init(computed);
    uchar b[32];
    hextouchars(in, 32, b);
    decode_scalar_25519(b, computed);
    assert(mpz_cmp(computed, expected) == 0);
    mpz_clear(computed);
}

void check_u_coords(char *in, mpz_t prime, mpz_t expected) {
    mpz_t computed;
    mpz_init(computed);
    uchar b[32];
    hextouchars(in, 32, b);

    decode_u_coord(b, 255, computed);
    assert(mpz_cmp(computed, expected) == 0);

    uchar ub[32];
    encode_u_coord(computed, 255, prime, ub);

    int eq = 1;
    for (int i = 0; i < 32; ++i) {
        if ((i < 31 && ub[i] != b[i]) || (i == 31 && ub[i] != (b[i] & 0x7F)))
            eq = 0;
    }
    assert(eq);

    mpz_clear(computed);
}

int main() {
    mpz_t expected, prime;
    mpz_inits(expected, prime, NULL);
    mpz_set_ui(prime, 1);
    mpz_mul_2exp(prime, prime, 255);
    mpz_sub_ui(prime, prime, 19);

    printf("Starting IO tests\n");

    // First test
    char in[] =
        "a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4";
    mpz_set_str(expected,
                "31029842492115040904895560451863089656472772604678260265531221"
                "036453811406496",
                10);
    check_scalar(in, expected);

    char uin[] =
        "e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c";
    mpz_set_str(expected,
                "34426434033919594451155107781188821651316167215306631574996226"
                "621102155684838",
                10);
    check_u_coords(uin, prime, expected);

    // Second test
    char in_[] =
        "4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d";
    mpz_set_str(expected,
                "35156891815674817266734212754503633747128614016119564763269015"
                "315466259359304",
                10);
    check_scalar(in_, expected);

    char uin_[] =
        "e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a493";
    mpz_set_str(expected,
                "88838573511839298940907593866106493194173388000221989452553959"
                "22347792736741",
                10);
    check_u_coords(uin_, prime, expected);

    printf("All IO tests passed\n");

    mpz_clears(expected, prime, NULL);
}
