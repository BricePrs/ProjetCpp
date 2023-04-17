//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();
    Universe<3> univers(pow(pow(2, 7), 3), Vector<3>(-1., -1., -1.), Vector<3>(1., 1., 1.), 0.01);
    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";

    univers.simulate_with_grid(1.0, 0.015);
}