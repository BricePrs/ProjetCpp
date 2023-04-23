//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();
    Universe<3> univers(Vector<3>(-1000.), Vector<3>(1000.), 300);
    univers.random_fill(pow(pow(2, 5), 3));
    univers.simulate_with_grid(1.0, 0.015);

    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";
}