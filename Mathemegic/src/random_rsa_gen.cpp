//#include<openssl/sha.h>
//#include<../include/random_rsa_gen.h>
//#include <prime_check.h>
//
//namespace Mathemagic {
//
//    uint1024_t generate_random_prime(mt19937_64& gen, int digit_length) {
//        if (digit_length <= 0) throw invalid_argument("Digit length must be positive.");
//        uniform_int_distribution<uint64_t> dist(0, 9);
//        string num_str = to_string(dist(gen) % 9 + 1); // First digit 1-9
//        for (int i = 1; i < digit_length; i++) {
//            num_str += to_string(dist(gen));
//        }
//        uint1024_t candidate = uint1024_t(num_str);
//        if (digit_length > 1) candidate |= 1; // Ensure odd
//        while (!Mathemagic::primality_check(candidate)) {
//            candidate += 2;
//        }
//        return candidate;
//    }
//
//    rand_RSAKeys generate_random_rsa_keys(uint64_t seed) {
//        std::mt19937_64 gen(seed);
//        uint1024_t prime1 = generate_random_prime(gen, 10);
//        uint1024_t prime2 = generate_random_prime(gen, 10);
//        while (prime2 == prime1) {
//            prime2 = generate_random_prime(gen, 10);
//        }
//
//        rand_RSAKeys keys;
//        keys.prime1 = prime1;
//        keys.prime2 = prime2;
//        keys.modulus = prime1 * prime2;
//        keys.totient = (prime1 - 1) * (prime2 - 1);
//
//        if (keys.totient == 0) {
//            throw std::runtime_error("Totient is zero, invalid prime pair.");
//        }
//
//        keys.p_exponent = 2;
//        while (gcd(keys.p_exponent, keys.totient) != 1) {
//            keys.p_exponent++;
//            if (keys.p_exponent >= keys.totient) {
//                throw std::runtime_error("No valid public exponent found.");
//            }
//        }
//
//        uint1024_t k = 1;
//        while (((k * keys.totient) + 1) % keys.p_exponent != 0) {
//            k++;
//            if (k > keys.totient) {
//                throw std::runtime_error("No valid private exponent found.");
//            }
//        }
//        keys.d_exponent = ((k * keys.totient) + 1) / keys.p_exponent;
//
//        return keys;
//    }
//
//}


#include "../include/random_rsa_gen.h"
#include "../include/random_prime.h"
#include "../include/prime_check.h"
#include <string>
#include <random>
#include <stdexcept>

namespace Mathemagic {

    uint1024_t generate_random_prime(std::mt19937_64& gen, int digit_length) {
        // Delegate to random_prime.cpp for consistency
        std::string num_str;
        std::uniform_int_distribution<int> digit_dist(0, 9);
        num_str += std::to_string(digit_dist(gen) % 9 + 1); // First digit 1-9
        for (int i = 1; i < digit_length; i++) {
            num_str += std::to_string(digit_dist(gen));
        }
        uint1024_t candidate = uint1024_t(num_str);
        if (digit_length > 1) candidate |= 1; // Ensure odd
        while (!primality_check(candidate)) {
            candidate += 2;
        }
        return candidate;
    }

    rand_RSAKeys generate_random_rsa_keys(uint64_t seed) {
        std::mt19937_64 gen(seed);
        uint1024_t prime1 = generate_random_prime(gen, 10);
        uint1024_t prime2 = generate_random_prime(gen, 10);
        while (prime2 == prime1) {
            prime2 = generate_random_prime(gen, 10);
        }

        rand_RSAKeys keys;
        keys.prime1 = prime1;
        keys.prime2 = prime2;
        keys.modulus = prime1 * prime2;
        keys.totient = (prime1 - 1) * (prime2 - 1);

        if (keys.totient == 0) {
            throw std::runtime_error("Totient is zero, invalid prime pair.");
        }

        keys.p_exponent = 2;
        while (gcd(keys.p_exponent, keys.totient) != 1) {
            keys.p_exponent++;
            if (keys.p_exponent >= keys.totient) {
                throw std::runtime_error("No valid public exponent found.");
            }
        }

        uint1024_t k = 1;
        while (((k * keys.totient) + 1) % keys.p_exponent != 0) {
            k++;
            if (k > keys.totient) {
                throw std::runtime_error("No valid private exponent found.");
            }
        }
        keys.d_exponent = ((k * keys.totient) + 1) / keys.p_exponent;

        return keys;
    }
}