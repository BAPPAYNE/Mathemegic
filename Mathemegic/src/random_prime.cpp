//#include "../include/random_prime.h"
//#include <random>
//#include <stdexcept>
//#include <iostream>
//
//namespace Mathemagic {
//    uint1024_t pow_mod(uint1024_t a, uint1024_t b, uint1024_t mod) {
//        uint1024_t res = 1;
//        a %= mod;
//        while (b > 0) {
//            if (b % 2 == 1) res = (res * a) % mod;
//            a = (a * a) % mod;
//            b /= 2;
//        }
//        return res;
//    }
//
//    bool is_prime(uint1024_t n, int k) {
//        if (n <= 1) return false;
//        if (n <= 3) return true;
//        if (n % 2 == 0) return false;
//
//        uint1024_t d = n - 1;
//        int s = 0;
//        while (d % 2 == 0) {
//            d /= 2;
//            s++;
//        }
//
//        std::random_device rd;
//        std::mt19937_64 gen(rd());
//        std::uniform_int_distribution<uint64_t> dis(2, (n - 2 > std::numeric_limits<uint64_t>::max()) ? std::numeric_limits<uint64_t>::max() : static_cast<uint64_t>(n - 2));
//
//        for (int i = 0; i < k; i++) {
//            uint1024_t a = dis(gen);
//            uint1024_t x = pow_mod(a, d, n);
//            if (x == 1 || x == n - 1) continue;
//
//            bool composite = true;
//            for (int j = 0; j < s - 1; j++) {
//                x = pow_mod(x, 2, n);
//                if (x == n - 1) {
//                    composite = false;
//                    break;
//                }
//            }
//            if (composite) return false;
//        }
//        return true;
//    }
//
//    uint1024_t random_number_with_digits(int digits) {
//        if (digits <= 0) throw std::invalid_argument("Digits must be positive.");
//        std::random_device rd;
//        std::mt19937 gen(rd());
//        uint1024_t min_val = pow(uint1024_t(10), digits - 1);
//        uint1024_t max_val = pow(uint1024_t(10), digits) - 1;
//        std::uniform_int_distribution<uint64_t> dist(static_cast<uint64_t>(min_val), static_cast<uint64_t>(max_val));
//        return dist(gen);
//    }
//
//    uint1024_t generate_prime_with_digits(int digit_length) {
//        if (digit_length <= 0) throw std::invalid_argument("Digit length must be positive.");
//        uint1024_t candidate;
//        do {
//            candidate = random_number_with_digits(digit_length);
//            if (digit_length > 1) candidate |= 1;  // Ensure odd
//        }while (!is_prime(candidate));
//        return candidate;
//    }
//
//    int getRandomNumber(int min, int max) {
//        std::random_device rd;
//        std::mt19937 gen(rd());
//        std::uniform_int_distribution<int> dist(min, max);
//        return dist(gen);
//    }
//}

#include "../include/random_prime.h"
#include <random>
#include <stdexcept>
#include <iostream>
#include <string>

namespace Mathemagic {
    static uint1024_t pow_mod(uint1024_t a, uint1024_t b, uint1024_t mod) {
        uint1024_t res = 1;
        a %= mod;
        while (b > 0) {
            if (b % 2 == 1) res = (res * a) % mod;
            a = (a * a) % mod;
            b /= 2;
        }
        return res;
    }

    bool is_prime(uint1024_t n, int k) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0) return false;

        uint1024_t d = n - 1;
        int s = 0;
        while (d % 2 == 0) {
            d /= 2;
            s++;
        }

        std::random_device rd;
        std::mt19937_64 gen(rd());
        // Use a fixed range for a that fits uint64_t, sufficient for Miller-Rabin
        std::uniform_int_distribution<uint64_t> dis(2, 1000000);  // Smaller range

        for (int i = 0; i < k; i++) {
            uint1024_t a = dis(gen);  // a is uint64_t, safe conversion to uint1024_t
            uint1024_t x = pow_mod(a, d, n);
            if (x == 1 || x == n - 1) continue;

            bool composite = true;
            for (int j = 0; j < s - 1; j++) {
                x = pow_mod(x, 2, n);
                if (x == n - 1) {
                    composite = false;
                    break;
                }
            }
            if (composite) return false;
        }
        return true;
    }

    uint1024_t random_number_with_digits(int digits) {
        if (digits <= 0) throw std::invalid_argument("Digits must be positive.");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> digit_dist(0, 9);

        std::string num_str;
        num_str += std::to_string(digit_dist(gen) + 1);  // First digit 1-9
        for (int i = 1; i < digits; i++) {
            num_str += std::to_string(digit_dist(gen));
        }

        return uint1024_t(num_str);
    }

    uint1024_t generate_prime_with_digits(int digit_length) {
        if (digit_length <= 0) throw std::invalid_argument("Digit length must be positive.");
        uint1024_t candidate;
        do {
            candidate = random_number_with_digits(digit_length);
            if (digit_length > 1) candidate |= 1;  // Ensure odd
        } while (!is_prime(candidate));
        return candidate;
    }

    int getRandomNumber(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }
}