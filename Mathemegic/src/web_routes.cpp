#include "../include/web_routes.h"
#include "../include/rsa_gen.h"
#include "../include/prime_check.h"
#include "../include/random_prime.h"
#include "../include/random_rsa_gen.h"
#include <openssl/sha.h>
#include <string>
#include <iostream>

namespace WebRoutes {
    crow::response home_page() {
        std::string html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <link rel="stylesheet" href="../static/style.css">
            <title>Mathemegic</title>
        </head>
        <body>
            <h1>Welcome to Mathemegic</h1>
            <h2>Mathematical Tools</h2>
            <ul>
                <li><a href="/prime-checker">Prime Number Checker</a></li>
                <li><a href="/rsa-generator">RSA Key Generator</a></li>
                <li><a href="/random_prime_generator">Random Prime Generator</a></li>
                <li><a href="/random_rsa_generator">Random RSA Generator</a></li>
            </ul>
        </body>
        </html>
        )";
        return crow::response(html);
    }

    crow::response prime_checker(const crow::request& req) {
        std::string result;
        if (req.method == "POST"_method) {
            auto params = req.get_body_params();
            auto x = params.get("number");
            if (x) {
                try {
                    uint1024_t num(x);
                    bool is_prime = Mathemagic::primality_check(num);
                    result = std::string(x) + (is_prime ? " is prime!" : " is not prime.");
                }
                catch (const std::exception& e) {
                    result = "Invalid input: " + std::string(e.what());
                }
            }
            else {
                result = "Please enter a number.";
            }
        }

        std::string html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <link rel="stylesheet" href="../static/style.css">
            <title>Prime Checker - Mathemegic</title>
        </head>
        <body>
            <h1>Prime Number Checker</h1>
            <form method="post" action="/prime-checker">
                <input type="number" name="number" placeholder="Enter a number">
                <input type="submit" value="Check">
            </form>
        )";
        if (!result.empty()) {
            html += "<p>" + result + "</p>";
        }
        html += R"(
            <p><a href="/">Back to Home</a></p>
        </body>
        </html>
        )";
        return crow::response(html);
    }

    crow::response rsa_generator(const crow::request& req) {
        std::string result;
        std::cout << "Entering rsa_generator...\n";

        if (req.method == "POST"_method) {
            std::cout << "Processing POST request...\n";
            auto params = req.get_body_params();
            auto p_str = params.get("prime1");
            auto q_str = params.get("prime2");
            std::cout << "Prime1: " << (p_str ? p_str : "null") << ", Prime2: " << (q_str ? q_str : "null") << "\n";

            if (p_str && q_str) {
                try {
                    std::cout << "Converting inputs to uint1024_t...\n";
                    uint1024_t p(p_str), q(q_str);
                    std::cout << "Generating RSA keys...\n";
                    Mathemagic::RSAKeys keys = Mathemagic::generate_rsa_keys(p, q);
                    std::cout << "Keys generated successfully.\n";
                    result = "Prime 1: " + keys.prime1.str() + "<br>";
                    result += "Prime 2: " + keys.prime2.str() + "<br>";
                    result += "Modulus (n): " + keys.modulus.str() + "<br>";
                    result += "Totient (φ): " + keys.totient.str() + "<br>";
                    result += "Public Exponent (e): " + keys.p_exponent.str() + "<br>";
                    result += "Private Exponent (d): " + keys.d_exponent.str();
                }
                catch (const std::exception& e) {
                    std::cout << "Exception caught: " << e.what() << "\n";
                    result = "Error: " + std::string(e.what());
                }
            }
            else {
                result = "Please enter both prime numbers.";
                std::cout << "Missing prime numbers.\n";
            }
        }

        std::cout << "Building HTML response...\n";
        std::string html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <link rel="stylesheet" href="../static/style.css">
            <title>RSA Generator - Mathemegic</title>
        </head>
        <body>
            <h1>RSA Key Generator</h1>
            <form method="post" action="/rsa-generator">
                <input type="number" name="prime1" placeholder="Enter first prime">
                <input type="number" name="prime2" placeholder="Enter second prime">
                <input type="submit" value="Generate Keys">
            </form>
        )";
        if (!result.empty()) {
            html += "<p>" + result + "</p>";
        }
        html += R"(
            <p><a href="/">Back to Home</a></p>
        </body>
        </html>
        )";
        std::cout << "Returning response...\n";
        return crow::response(html);
    }

    crow::response random_prime_generator(const crow::request& req) {
        std::string result;
        std::cout << "Entering random_prime_generator...\n";
        if (req.method == "POST"_method) {
            std::cout << "Processing POST request...\n";
            auto params = req.get_body_params();
            auto length1 = params.get("length1");
            std::cout << "Length: " << (length1 ? length1 : "null") << "\n";

            if (length1) {
                try {
                    int prime_length = std::stoi(length1);
                    if (prime_length <= 0) throw std::invalid_argument("Length must be positive.");
                    std::cout << "Generating Random Prime...\n";
                    uint1024_t random_prime_result = Mathemagic::generate_prime_with_digits(prime_length);
                    std::cout << "Prime Generated Successfully.\n";
                    result = "Generated Prime: " + random_prime_result.str() + "<br>";
                    result += "Prime Length: " + std::to_string(prime_length) + "<br>";
                }
                catch (const std::exception& e) {
                    std::cout << "Exception caught: " << e.what() << "\n";
                    result = "Error: " + std::string(e.what());
                }
            }
            else {
                result = "Please specify a length.";
                std::cout << "Missing length.\n";
            }
        }

        std::cout << "Building HTML response...\n";
        std::string html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <link rel="stylesheet" href="/style.css">
            <title>Random Prime Generator - Mathemegic</title>
        </head>
        <body>
            <h1>Random Prime Generator</h1>
            <form method="post" action="/random_prime_generator">
                <input type="number" name="length1" placeholder="Specify length">
                <input type="submit" value="Generate Random Prime">
            </form>
        )";
        if (!result.empty()) {
            html += "<p>" + result + "</p>";
        }
        html += R"(
            <p><a href="/">Back to Home</a></p>
        </body>
        </html>
        )";
        std::cout << "Returning response...\n";
        return crow::response(html);
    }

    crow::response random_rsa_generator(const crow::request& req) {
        std::string result;
        std::cout << "Entering random_rsa_generator...\n";

        if (req.method == "POST"_method) {
            std::cout << "Processing POST request...\n";
            auto params = req.get_body_params();
            auto entropy = params.get("entropy");

            if (entropy) {
                try {
                    // Hash entropy to create a seed
                    unsigned char hash[SHA256_DIGEST_LENGTH];
                    SHA256(reinterpret_cast<const unsigned char*>(entropy), strlen(entropy), hash);
                    uint64_t seed = 0;
                    for (int i = 0; i < 8; ++i) {
                        seed = (seed << 8) | hash[i];
                    }

                    std::cout << "Generating RSA keys with seed...\n";
                    Mathemagic::rand_RSAKeys keys = Mathemagic::generate_random_rsa_keys(seed);
                    std::cout << "Keys generated successfully.\n";
                    result = "Prime 1: " + keys.prime1.str() + "<br>";
                    result += "Prime 2: " + keys.prime2.str() + "<br>";
                    result += "Modulus (n): " + keys.modulus.str() + "<br>";
                    result += "Totient (φ): " + keys.totient.str() + "<br>";
                    result += "Public Exponent (e): " + keys.p_exponent.str() + "<br>";
                    result += "Private Exponent (d): " + keys.d_exponent.str();
                }
                catch (const std::exception& e) {
                    std::cout << "Exception caught: " << e.what() << "\n";
                    result = "Error: " + std::string(e.what());
                }
            }
            else {
                result = "Please provide entropy by moving the mouse.";
                std::cout << "Missing entropy.\n";
            }
        }

        std::cout << "Building HTML response...\n";
        std::string html = R"(
<!DOCTYPE html>
        <html>
        <head>
            <link rel="stylesheet" href="../static/style.css">
            <title>Random RSA Generator - Mathemegic</title>
        </head>
        <body>
            <h1>Random RSA Generator</h1>
            <canvas id="entropyCanvas" width="250" height="100"></canvas>
            <div id="progressBar"><div></div></div>
            <form method="post" action="/random_rsa_generator">
                <input type="hidden" name="entropy" id="entropy">
                <input type="submit" value="Generate Keys" id="generateButton">
            </form>
            <script>
                const canvas = document.getElementById('entropyCanvas');
                const ctx = canvas.getContext('2d');
                const progressBar = document.querySelector('#progressBar div');
                const entropyInput = document.getElementById('entropy');
                const generateButton = document.getElementById('generateButton');
                let entropyData = [];
                let entropyCount = 0;
                const maxEntropy = 100;

                ctx.fillStyle = '#0d0d0d';
                ctx.fillRect(0, 0, canvas.width, canvas.height);
                ctx.font = '12px Courier New';
                ctx.fillStyle = '#00ffcc';
                ctx.fillText('Move mouse here', 10, 50);

                canvas.addEventListener('mousemove', (e) => {
                    if (entropyCount >= maxEntropy) return;

                    const rect = canvas.getBoundingClientRect();
                    const x = e.clientX - rect.left;
                    const y = e.clientY - rect.top;
                    const time = Date.now();

                    entropyData.push(`${x},${y},${time}`);
                    entropyCount++;

                    const progress = (entropyCount / maxEntropy) * 100;
                    progressBar.style.width = `${progress}%`;

                    ctx.fillStyle = '#ff00cc';
                    ctx.fillRect(x, y, 2, 2);

                    if (entropyCount >= maxEntropy) {
                        entropyInput.value = entropyData.join(';');
                        generateButton.style.display = 'block';
                        ctx.fillStyle = '#0d0d0d';
                        ctx.fillRect(0, 0, canvas.width, canvas.height);
                        ctx.fillStyle = '#00ffcc';
                        ctx.fillText('Entropy collected!', 10, 50);
                    }
                });
            </script>
        )";
        if (!result.empty()) {
            html += "<p>" + result + "</p>";
        }
        html += R"(
            <p><a href="/">Back to Home</a></p>
        </body>
        </html>
        )";
        std::cout << "Returning response...\n";
        return crow::response(html);
    }
}