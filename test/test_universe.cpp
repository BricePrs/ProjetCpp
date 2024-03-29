#include <iostream>
#include <chrono>
#include "Particle.h"
#include "Universe.h"

int main() {
    SimulationConstraints constraints = SimulationConstraints(Vector<3>(-3.), Vector<3>(3.));
    SimulationSettings settings = SimulationSettings();
    settings.physics_time_step = 0.015;
    settings.physics_time_total = 468.5;
    settings.iter_count_until_save = 400;



    std::string source_path = __FILE__;
    size_t last_separator = source_path.find_last_of("/\\");
    std::string file_path = source_path.substr(0, last_separator + 1) + "dat_files/universe_perf_insertion.dat";
    std::ofstream file(file_path);

    for (int i =0; i<9; i++) {
        Universe<3> univers(constraints, 1.0);

        auto start = std::chrono::steady_clock::now();
        univers.random_fill(pow(pow(2, i), 3));
        std::chrono::duration<double> filling_elapsed_time = std::chrono::steady_clock::now() - start;
        std::cout << "Time elapsed for a universe with 2^(3*"<< i << ") particles : " << filling_elapsed_time.count() << "s\n";


        file << univers.get_particles_count() << " " << filling_elapsed_time.count() << "\n";
    }
    file.close();

    file_path = source_path.substr(0, last_separator + 1) + "dat_files/universe_perf_simulation.dat";
    std::ofstream file2(file_path);

    for (int i = 0; i<16; i++) {
        printf("iteration i=%i", i);
        Universe<3> univers(constraints, 1.0);
        univers.random_fill(pow(2, i));

        auto start = std::chrono::steady_clock::now();
        univers.simulate(settings);
        std::chrono::duration<double> simulating_time_elapsed = std::chrono::steady_clock::now() - start;

        file2 << univers.get_particles_count() << " " << simulating_time_elapsed.count() << "\n";
    }
    file2.close();


}