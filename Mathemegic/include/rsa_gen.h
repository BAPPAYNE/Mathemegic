#pragma once
#include <cmath>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

namespace Mathemagic {
    struct RSAKeys {
        uint1024_t prime1;
        uint1024_t prime2;
        uint1024_t modulus;
        uint1024_t totient;
        uint1024_t p_exponent;  // Public exponent
        uint1024_t d_exponent;  // Private exponent
    };
    RSAKeys generate_rsa_keys(uint1024_t prime1, uint1024_t prime2);
    //bool primality_check_2(uint1024_t num);
}