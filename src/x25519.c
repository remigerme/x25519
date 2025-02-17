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
    mpz_t m, a24, mod;
    mpz_inits(m, a24, mod, NULL);

    // Common parameters
    mpz_set_ui(mod, 1);
    mpz_mul_2exp(mod, mod, 255);
    mpz_sub_ui(mod, mod, 19);

    mpz_set_ui(a24, 121666);

    point res;
    point_init(&res);

    // Reading m
    uchar mbuf[32];
    hextouchars(argv[1], 32, mbuf);

    decode_scalar_25519(mbuf, m);

    // Starting point
    point p;
    point_init(&p);
    if (argc == 2) {
        mpz_set_ui(p.x, 9);
        mpz_set_ui(p.z, 1);
    } else {
        uchar ubuf[32];
        hextouchars(argv[2], 32, ubuf);
        decode_u_coord(ubuf, 255, p.x);
        mpz_set_ui(p.z, 1);
    }
    ladder(&res, m, p, a24, mod);

    uchar ub[32];
    encode_u_coord(res.x, 255, mod, ub);

    // Printing output
    for (int i = 0; i < 32; ++i)
        printf("%02x", ub[i]);
    printf("\n");

    // Free time
    mpz_clears(m, a24, mod, NULL);
    point_clear(&res);
    point_clear(&p);
}
