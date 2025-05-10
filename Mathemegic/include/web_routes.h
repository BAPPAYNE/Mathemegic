#pragma once
#include <crow.h>

namespace WebRoutes {
    crow::response home_page();
    crow::response prime_checker(const crow::request& req);
    crow::response rsa_generator(const crow::request& req);
    crow::response random_prime_generator(const crow::request& req);
    crow::response random_rsa_generator(const crow::request& req);
}