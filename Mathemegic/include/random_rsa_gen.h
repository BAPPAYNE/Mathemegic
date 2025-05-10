#pragma once
#include <stdexcept>
#include<iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <random>
#include <rsa_gen.h>

using boost::multiprecision::uint1024_t;
using namespace std;
namespace Mathemagic {

    struct rand_RSAKeys {
        uint1024_t prime1;
        uint1024_t prime2;
        uint1024_t modulus;
        uint1024_t totient;
        uint1024_t p_exponent;
        uint1024_t d_exponent;
    };

    uint1024_t generate_random_prime(mt19937_64& gen, int digit_length);
    rand_RSAKeys generate_random_rsa_keys(uint64_t seed);
}