//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();
    Universe<3> univers(Vector<3>(-200.), Vector<3>(200.), 2.5);

    double spacing = pow(2., 1./6.)*.1;

    int a = univers.add_packed_particles(Vector<3>(-20., 20., -20.)*spacing+Vector<3>(0., 5., 0.), Vector<3>(20., 60., 20.)*spacing+Vector<3>(0., 5., 0.), Vector<3>(0., -10., 0.), 1., NEUTRON, Vector<3>(4, 4, 4));
    int b = univers.add_packed_particles(Vector<3>(-80., -20., -80.)*spacing, Vector<3>(80., 20., 80.)*spacing, Vector<3>(0.), 1., NEUTRON, Vector<3>(16, 4, 16));

    std::cout << "Instantiating " << a << " and " << b << " particles." << std::endl;

    univers.simulate(19.5, 0.00005, false, true, true, 2000);

    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";
}