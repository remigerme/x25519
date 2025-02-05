# x25519

The code have been implemented using [RFC 7748](https://datatracker.ietf.org/doc/html/rfc7748) and slides from INF568 course.

## Installation

```shell
make
```

This builds one target : `x25519`.

## Tests

The following command will compile and run tests automatically :

```shell
make tests
```

Information about performed tests will be displayed. If a test fails it returns an error code, otherwise it returns with code 0 if successfull.

All tests given in the RFC are implemented. Note that by default, the iterative test described in section 5.2 only does 1000 iterations. You can set this number to 1000000 to have all tests (estimated runtime : 30min).

Code implemented for the "Advanced Cryptology" course at École polytechnique by Rémi Germe.
