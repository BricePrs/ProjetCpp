#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
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

    PhysicsConstants constants = {
            .eps =  5.,
            .sigma =  1.
    };

    auto settings = SimulationSettings {
        .lennard_jones_interaction = true,
        .physics_time_step = .00005,
        .physics_time_total = .5,
        .iter_count_until_save = 2000,
        .boundary_behaviour = Absorption,
        .constants = constants
    };

    universe.simulate(settings);
}