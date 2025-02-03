#include "montgomery.h"

#include <assert.h>
#include <stdio.h>

void small_curve_1() {
    mpz_t m, mod, a24;
    mpz_inits(m, mod, a24, NULL);

    mpz_set_ui(mod, 101);
    mpz_set_ui(a24, 38);

    point rop;
    point_init(&rop);

    point p;
    point_init(&p);
    mpz_set_ui(p.x, 2);
    mpz_set_ui(p.z, 1);

    // Checking xdbl
    xdbl(&rop, p, a24, mod);
    assert(mpz_cmp_ui(rop.x, 70) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    // Checking xadd
    xadd(&rop, rop, p, p, mod);
    assert(mpz_cmp_ui(rop.x, 59) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    // Checking ladder
    mpz_set_ui(m, 77);
    ladder(&rop, m, p, a24, mod);
    assert(mpz_cmp_ui(rop.x, 8) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    point_clear(&rop);
    point_clear(&p);
    mpz_clears(m, mod, a24, NULL);
}

void small_curve_2() {
    mpz_t m, mod, a24;
    mpz_inits(m, mod, a24, NULL);

    mpz_set_ui(mod, 1009);
    mpz_set_ui(a24, 171);

    point rop;
    point_init(&rop);

    point p;
    point_init(&p);
    mpz_set_ui(p.x, 7);
    mpz_set_ui(p.z, 1);

    // Checking xdbl
    xdbl(&rop, p, a24, mod);
    assert(mpz_cmp_ui(rop.x, 284) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    // Checking xadd
    xadd(&rop, rop, p, p, mod);
    assert(mpz_cmp_ui(rop.x, 759) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    // Checking ladder
    mpz_set_ui(m, 104);
    ladder(&rop, m, p, a24, mod);
    assert(mpz_cmp_ui(rop.x, 810) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    mpz_set_ui(m, 947);
    ladder(&rop, m, p, a24, mod);
    assert(mpz_cmp_ui(rop.x, 755) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    point_clear(&rop);
    point_clear(&p);
    mpz_clears(m, mod, a24, NULL);
}

void curve25519() {
    mpz_t m, mod, a24, res;
    mpz_inits(m, mod, a24, res, NULL);

    mpz_set_ui(mod, 1);
    mpz_mul_2exp(mod, mod, 255);
    mpz_sub_ui(mod, mod, 19);

    mpz_set_ui(a24, 121666);

    point rop;
    point_init(&rop);

    point p;
    point_init(&p);
    mpz_set_ui(p.x, 9);
    mpz_set_ui(p.z, 1);

    // Checking xdbl
    xdbl(&rop, p, a24, mod);
    mpz_set_str(res,
                "14847277145635483483963372537557091634710985132825781088887140"
                "890597596352251",
                10);
    assert(mpz_cmp(rop.x, res) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    // Checking xadd
    xadd(&rop, rop, p, p, mod);
    mpz_set_str(res,
                "12697861248284385512127539163427099897745340918349830473877503"
                "196793995869202",
                10);
    assert(mpz_cmp(rop.x, res) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    // Checking ladder
    mpz_set_ui(m, 7);
    ladder(&rop, m, p, a24, mod);
    mpz_set_str(res,
                "61896166079956151933671508773760055139029891634704022903956041"
                "16858034460712",
                10);
    assert(mpz_cmp(rop.x, res) == 0 && mpz_cmp_ui(rop.z, 1) == 0);

    point_clear(&rop);
    point_clear(&p);
    mpz_clears(m, mod, a24, res, NULL);
}

int main() {
    printf("Starting tests on montgomery\n");

    small_curve_1();
    printf("All tests passed for small_curve_1\n");

    small_curve_2();
    printf("All tests passed for small_curve_2\n");

    curve25519();
    printf("All tests passed for curve25519\n");
}
