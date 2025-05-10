#include "../include/rsa_gen.h"
#include "../include/prime_check.h"
#include <string>
#include <random>

using namespace std;

namespace Mathemagic {
    uint1024_t gcd(uint1024_t a, uint1024_t b) {
        while (b != 0) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    RSAKeys generate_rsa_keys(uint1024_t prime1, uint1024_t prime2) {
        if (prime1 == 0 || prime2 == 0) {
            throw invalid_argument("Prime numbers cannot be zero.");
        }

        RSAKeys keys;
        keys.prime1 = prime1;
        keys.prime2 = prime2;

        if (!primality_check(prime1) || !primality_check(prime2)) {
            throw invalid_argument("Both inputs must be prime numbers.");
        }

        keys.modulus = prime1 * prime2;
        keys.totient = (prime1 - 1) * (prime2 - 1);

        if (keys.totient == 0) {
            throw runtime_error("Totient is zero, invalid prime pair.");
        }

        keys.p_exponent = 2;
        while (gcd(keys.p_exponent, keys.totient) != 1) {
            keys.p_exponent++;
            if (keys.p_exponent >= keys.totient) {
                throw runtime_error("No valid public exponent found.");
            }
        }

        uint1024_t k = 1;
        while (((k * keys.totient) + 1) % keys.p_exponent != 0) {
            k++;
            if (k > keys.totient) {
                throw runtime_error("No valid private exponent found.");
            }
        }
        keys.d_exponent = ((k * keys.totient) + 1) / keys.p_exponent;

        return keys;
    }
}