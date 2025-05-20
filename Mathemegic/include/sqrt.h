#pragma once 
#include<boost/multiprecision/cpp_bin_float.hpp>
#include "../include/common.h"
using namespace std;
using namespace boost::multiprecision;
using namespace Mathemagic;
using big_float = cpp_bin_float_100;

namespace SQRT {
    big_float func(big_float N, big_float x) {
        return x * x - N;
    }

    big_float sqrt_Bisection(big_float N) {
        if (N == 0 || N == 1) {
            return N;
        }
        if (N < 0) {
            cerr << "\033[0;31mN cannot be negative. \033[0m" << endl;
            return 0;
        }
        big_float x;
        big_float a, b, c;
        cout.precision(500);       // set precision for printing max length after point.
        if (N < 0) {
            cerr << "\033[0;31mN cannot be negative. \033[0m" << endl;
            return 0;
        }
        if (N > 1) {
            a = 0;  b = N;
        }
        else {
            a = N;  b = 1;
        }
        long long count = 99;
        while (count) {               // count - Looping or iteration variable.
            c = a + (b - a) / 2.0;
            if (func(N, a) * func(N, c) < 0) {        // Checking bisection method condition and updating $a and $b accordingly.
                b = c;
            }
            else {
                a = c;
            }
            count--;
        }
        return c;
    }

    big_float sqrt_Regula_Falsi(big_float N) {
        if (N == 0 || N == 1) {
            return N;
        }
        if (N < 0) {
            cerr << "\033[0;31mN cannot be negative. \033[0m" << endl;
            return 0;
        }
        big_float a, b, c;
        if (N > 1) {
            b = N;  a = 0;
        }
        else {
            a = N;  b = 0;
        }

        long long count = 99;
        while (count) {   // count - Looping or iteration variable.
            // c = (a*func(N,b) - b*func(N,a))/(func(N,b)-func(N,a)) ; // 4 function calls
            // Checking bisection method condition and updating $a and $b accordingly.
            c = (b - (func(N, b) * (b - a)) / (func(N, b) - func(N, a)));   // 3 function calls (more efficient)
            if (func(N, c) > 0) {
                a = c;
            }
            else {
                b = c;
            }
            count--;
        }
        return c;
    }
}