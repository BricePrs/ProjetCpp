//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();

    SimulationConstraints constraints = SimulationConstraints(Vector<2>(-3.), Vector<2>(3.));
    Universe<2> universe(constraints, 2.5);


    universe.add(
            Vector<2>(0., 2.),
            Vector<2>(10., 10.),
            1.,
            NEUTRON
    );

    auto settings = SimulationSettings {
        false,
        true,
        true,
        -1.,
        0.00005,
        5.,
        100,
        1000,
        Reflexive
    };

    universe.simulate(settings);

    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";
}