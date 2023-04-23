//
// Created by brice on 13/04/23.
//
#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    auto start = std::chrono::steady_clock::now();
    Universe<2> univers(Vector<2>(-50.), Vector<2>(50.), 100);
    univers.add(Vector<2>(0., 0.), Vector<2>(0., 0.), 1., Category::NEUTRON);
    univers.add(Vector<2>(0., 1.), Vector<2>(-1., 0.), 3.0e-6, Category::NEUTRON);
    univers.add(Vector<2>(0., 5.36), Vector<2>(-0.425, 0.), 9.55e-4, Category::NEUTRON);
    univers.add(Vector<2>(34.75, 0.), Vector<2>(0., 0.0296), 1.0e-14, Category::NEUTRON);
    univers.simulate(468.5, 0.015, true, false, true, 400);


    std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;
    std::cout << "Time elapsed for a universe " << elapsed_seconds.count() << "s\n";
}