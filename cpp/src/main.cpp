#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

double estimate_pi(std::uint64_t n, std::uint32_t seed = 42) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::uint64_t inside = 0;
    for (std::uint64_t i = 0; i < n; ++i) {
        const double x = dist(rng);
        const double y = dist(rng);
        if (x * x + y * y <= 1.0) inside++;
    }
    return 4.0 * static_cast<double>(inside) / static_cast<double>(n);
}

int main(int argc, char** argv) {

    std::uint64_t n = 2'000'000;   // valor por defecto

    // Si el usuario pasó un número, úsalo
    if (argc >= 2) {
        n = std::stoull(argv[1]);
    }

    const auto t0 = std::chrono::high_resolution_clock::now();
    const double pi_hat = estimate_pi(n);
    const auto t1 = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> dt = t1 - t0;

    std::cout << "[C++] n=" << n
              << "  pi~" << std::fixed << std::setprecision(6) << pi_hat
              << "  time=" << dt.count() << "s\n";
    return 0;
}