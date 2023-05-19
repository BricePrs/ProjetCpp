#include "Particle.h"
#include "Universe.h"

int main() {

    // simulation constraints
    SimulationConstraints constraints = SimulationConstraints(Vector<2>(-50.), Vector<2>(50.));
    Universe<2> univers(constraints, 100);

    // filling our universe with celestial bodies (=particles)
    univers.add(Vector<2>(0., 0.), Vector<2>(0., 0.), 1., Category::NEUTRON);
    univers.add(Vector<2>(0., 1.), Vector<2>(-1., 0.), 3.0e-6, Category::NEUTRON);
    univers.add(Vector<2>(0., 5.36), Vector<2>(-0.425, 0.), 9.55e-4, Category::NEUTRON);
    univers.add(Vector<2>(34.75, 0.), Vector<2>(0., 0.0296), 1.0e-14, Category::NEUTRON);

    // simulation settings
    SimulationSettings settings = SimulationSettings();
    settings.physics_time_step = 0.015;
    settings.physics_time_total = 468.5;
    settings.iter_count_until_save = 400;

    // running the simulation !
    univers.simulate(settings);
}