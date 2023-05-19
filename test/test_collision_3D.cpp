#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    SimulationConstraints constraints = SimulationConstraints(Vector<3>(-200.), Vector<3>(200.));
    Universe<3> univers(constraints, 2.5);

    double spacing = pow(2., 1./6.)*.1;

    int a = univers.add_packed_particles(Vector<3>(-20., 20., -20.)*spacing+Vector<3>(0., 5., 0.), Vector<3>(20., 60., 20.)*spacing+Vector<3>(0., 5., 0.), Vector<3>(0., -10., 0.), 1., NEUTRON, Vector<3>(4, 4, 4));
    int b = univers.add_packed_particles(Vector<3>(-80., -20., -80.)*spacing, Vector<3>(80., 20., 80.)*spacing, Vector<3>(0.), 1., NEUTRON, Vector<3>(16, 4, 16));

    std::cout << "Instantiating " << a << " and " << b << " particles." << std::endl;

    SimulationSettings settings = SimulationSettings();
    settings.lennard_jones_interaction = true;
    settings.physics_time_total = 19.5;
    settings.physics_time_step = 0.00005;
    settings.iter_count_until_save = 2000;
    univers.simulate(settings);

}