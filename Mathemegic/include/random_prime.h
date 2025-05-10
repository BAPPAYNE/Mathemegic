#pragma once
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

namespace Mathemagic {
    uint1024_t pow_mod(uint1024_t a, uint1024_t b, uint1024_t mod);
    bool is_prime(uint1024_t n, int k = 5);
    uint1024_t random_number_with_digits(int digits);
    uint1024_t generate_prime_with_digits(int digit_length);
    int getRandomNumber(int min, int max);
}