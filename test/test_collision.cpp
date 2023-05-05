//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();
    Universe<2> univers(Vector<2>(-150.), Vector<2>(150.), 2.5, Absorption);

    double spacing = pow(2., 1./6.);

    int a = univers.add_packed_particles(Vector<2>(-20., 20.)*spacing+Vector<2>(0., 5.), Vector<2>(20., 60.)*spacing+Vector<2>(0., 5.), Vector<2>(0., -10.), 1., NEUTRON, Vector<2>(40, 40));
    int b = univers.add_packed_particles(Vector<2>(-80., -20.)*spacing, Vector<2>(80., 20.)*spacing, Vector<2>(0., 0.), 1., NEUTRON, Vector<2>(160, 40));

    std::cout << "Instantiating " << a << " and " << b << " particles." << std::endl;

    univers.simulate(19.5, 0.05, false, true, true, 200);

    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";
}