#include <iostream>
#include <array>
#include <cstddef>

constexpr size_t max_value = 1000000;
constexpr size_t array_size = max_value - 2; // For 2 to max_value (inclusive)

constexpr auto generate_sieve() {
    std::array<bool, array_size> sieve{}; // All values default to false

    // Implement the Sieve of Eratosthenes
    for (size_t i = 2; i * i < max_value; i++) {
        if (!sieve[i - 2]) { // If this number is not marked
            for (size_t j = i * i; j < max_value; j += i) {
                sieve[j - 2] = true; // Mark multiples as true (composite)
            }
        }
    }

    return sieve;
}

constexpr auto sieve = generate_sieve();

int main() {
    // Now you can use primes array
    // For example, print out the first 10 primes
    for (int i = 0; i < 10; i++) {
        std::cout << primes[i] << std::endl;
    }

    return 0;
}