//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();


    SimulationConstraints constraints = SimulationConstraints(Vector<2>(0.), Vector<2>(250., 180.));
    Universe<2> universe(constraints, 2.5);

    double spacing = pow(2., 1./6.);

    int a = universe.add_packed_particles(
            Vector<2>(spacing),
            Vector<2>(250.-spacing, 35.*spacing),
            Vector<2>(0., 0.),
            1.,
            NEUTRON,
            Vector<2>(292., 59.)
    );

    int b = universe.fill_disk(
            Vector<2>(125., 125.),
            spacing,
            Vector<2>(0., -10.),
            1.,
            NEUTRON,
            395
    );

    std::cout << "Instantiating " << a << " and " << b << " particles." << std::endl;


    PhysicsConstants constants = {
            -12.,
            1.,
            1.
    };

    auto settings = SimulationSettings {
            true,
            false,
            true,
            0.005,
            0.00005,
            29.5,
            1000,
            1000,
            Reflexive,
            constants
    };

    universe.simulate(settings);

    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";
}
