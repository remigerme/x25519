#include <stdio.h>

#include "montgomery.h"
#include "montgomery_io.h"

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "[Usage] ./x25519 m [u]\n"
                        "Where :\n"
                        "\tm : \n"
                        "\tu : optional, starting point (default is (9, 1))\n");
        return 1;
    }
    mpz_t m, p, res;
    mpz_inits(m, p, res, NULL);

    // Reading m
    uchar mbuf[32];
    hextouchars(argv[1], 32, mbuf);

    decode_scalar_25519(mbuf, m);

    // Starting point
    if (argc == 2)
        mpz_set_ui(p, 9);
    else {
        uchar ubuf[32];
        hextouchars(argv[2], 32, ubuf);
        decode_u_coord(ubuf, 255, p);
    }

    curve25519_ladder(res, m, p);

    uchar ub[32];
    encode_u_coord_25519(res, 255, ub);

    // Printing output
    for (int i = 0; i < 32; ++i)
        printf("%02x", ub[i]);
    printf("\n");

    // Free time
    mpz_clears(m, p, res, NULL);
}
