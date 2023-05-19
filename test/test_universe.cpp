#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    SimulationConstraints constraints = SimulationConstraints(Vector<3>(-3.), Vector<3>(3.));

    // creating the same universe (same constraints) and filling it with 2^k particles
    for (int i =3; i<=7; i+=2) {
        auto start = std::chrono::steady_clock::now();
        Universe<3> univers(constraints, 1.0);
        univers.random_fill(pow(pow(2, i), 3));
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
        std::cout << "Time elapsed for a universe with 2^(3*"<< i << ") particles : " << elapsed_seconds.count() << "s\n";
    }
}