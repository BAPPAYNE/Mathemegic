//#include <crow.h>
//#include "../include/web_routes.h"
//#include <iostream>
//
//using namespace std;
//
//int main() {
//    crow::SimpleApp app;
//
//    std::cout << "Registering routes...\n";
//    CROW_ROUTE(app, "/")(WebRoutes::home_page);
//    CROW_ROUTE(app, "/prime-checker")
//        .methods("GET"_method, "POST"_method)(WebRoutes::prime_checker);
//    CROW_ROUTE(app, "/rsa-generator")
//        .methods("GET"_method, "POST"_method)(WebRoutes::rsa_generator);
//    CROW_ROUTE(app, "/random_prime_generator")
//        .methods("GET"_method, "POST"_method)(WebRoutes::random_prime_generator);
//    CROW_ROUTE(app, "/random_rsa_generator")
//        .methods("GET"_method, "POST"_method)(WebRoutes::random_rsa_generator);
//
//    CROW_ROUTE(app, "/style.css")([]() {
//        std::ifstream file("../static/style.css", ios::binary);
//        if (!file.is_open()) {
//            return crow::response(404, "CSS file not found");
//        }
//        std::stringstream buffer;
//        buffer << file.rdbuf();
//        crow::response res(buffer.str());
//        res.set_header("Content-Type", "text/css");
//        return res;
//        });
//
//
//    std::cout << "Starting server on port 18080...\n";
//    app.port(18080).multithreaded().run();
//    std::cout << "Server stopped.\n";
//    return 0;
//}


#include <crow.h>
#include "../include/web_routes.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    crow::SimpleApp app;

    std::cout << "Registering routes...\n";
    CROW_ROUTE(app, "/")(WebRoutes::home_page);
    CROW_ROUTE(app, "/prime-checker")
        .methods("GET"_method, "POST"_method)(WebRoutes::prime_checker);
    CROW_ROUTE(app, "/rsa-generator")
        .methods("GET"_method, "POST"_method)(WebRoutes::rsa_generator);
    CROW_ROUTE(app, "/random_prime_generator")
        .methods("GET"_method, "POST"_method)(WebRoutes::random_prime_generator);
    CROW_ROUTE(app, "/random_rsa_generator")
        .methods("GET"_method, "POST"_method)(WebRoutes::random_rsa_generator);

    CROW_ROUTE(app, "/style.css")([]() {
        std::ifstream file("../../Mathemegic/static/style.css", std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open static/style.css\n";
            return crow::response(404, "CSS file not found");
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/css");
        return res;
        });


    CROW_ROUTE(app, "/button_animation.js")([]() {
        std::ifstream file("../../Mathemegic/static/button_animation.js", std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open static/button_aninmation.js\n";
            return crow::response(404, "CSS file not found");
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        crow::response res(buffer.str());
        res.set_header("Content-Type", "text/js");
        return res;
        });

    std::cout << "Starting server on port 18080...\n";
    app.port(18080).multithreaded().run();
    std::cout << "Server stopped.\n";
    return 0;
}