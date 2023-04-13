//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Univers.h"

int main() {
    auto start = std::chrono::steady_clock::now();
    Univers univers = Univers(pow(pow(2, 3), 3));
    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count();

    univers.stromer_verlet(1.0, 0.015);
}