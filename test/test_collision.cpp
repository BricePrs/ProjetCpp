//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();

    SimulationConstraints constraints = SimulationConstraints(Vector<2>(-150.), Vector<2>(150.));
    Universe<2> universe(constraints, 2.5);

    double spacing = pow(2., 1./6.);

    int a = universe.add_packed_particles(
            Vector<2>(-20., 20.)*spacing+Vector<2>(0., 5.),
            Vector<2>(20., 60.)*spacing+Vector<2>(0., 5.),
            Vector<2>(0., -10.),
            1.,
            NEUTRON,
            Vector<2>(40, 40)
    );

    int b = universe.add_packed_particles(
            Vector<2>(-80., -20.)*spacing,
            Vector<2>(80., 20.)*spacing,
            Vector<2>(0., 0.),
            1.,
            NEUTRON,
            Vector<2>(160, 40)
    );

    std::cout << "Instantiating " << a << " and " << b << " particles." << std::endl;

    auto settings = SimulationSettings {
        false,
        false,
        true,
        -1.,
        0.00005,
        19.5,
        2000,
        1000,
        Periodic
    };

    universe.simulate(settings);

    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";
}