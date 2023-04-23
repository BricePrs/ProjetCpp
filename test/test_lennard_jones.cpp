//
// Created by helen on 14/04/23.
//
/**
 * Test that displays Lennard-Jones potential for a system composed of 2 particles.
 * This test answers to the first question of Lab 4.
 *
 * Here are the commands to execute in gnuplot (each command needs to be on separate lines)
 * after running the test to display the actual graph:
 * set xlabel "r"
 * set ylabel "U"
 * set xzeroaxis lt -1 lw 1
 * set yrange [-3: 5]
 * plot "lennard_jones.dat" u 1:2 with line lt2 title "U (Lennard Jones' potential)
 *
 * Notes:
 * F (interaction based on Lennard Jones' potential) is repulsive when 0 <= r < 1.12 and attractive when r > 1.12
 * when r = 1.12, the 2 particles are in equilibrium (F=0).
 */

#include <vector>
#include <Particle.h>
#include <fstream>

auto new_random_vec3(std::mt19937 &gen, std::uniform_real_distribution<double> &distribution) -> Vector<3> {
    return Vector<3>{distribution(gen), distribution(gen), distribution(gen)};
}

auto new_random_double(std::mt19937 &gen, std::uniform_real_distribution<double> &distribution) -> double {
    return distribution(gen);
}

std::vector<Particle<3>> generate_particles_vector(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-500.0, 500.0);

    // particle set creations
    std::vector<Particle<3>> particles_vector(nb_particles);

    for (uint i = 0; i < nb_particles; i++ ) {
        Particle new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_vector[i] = new_part;
    }
    return particles_vector;
}



void lennard_jones_potential(std::vector<Particle<3>> particles) {

    std::string source_path = __FILE__;
    size_t last_separator = source_path.find_last_of("/\\");
    std::string file_path = source_path.substr(0, last_separator + 1) + "lennard_jones.dat";

    std::ofstream file(file_path);

    double eps = 1.0;
    double sigma = 1.0;
    double sigma_exp_six = sigma * sigma * sigma * sigma * sigma * sigma;

    double r = 0.0;
    double dr = 0.01;
    double r_max = 3.0 * sigma;
    double u;

    while (r < r_max) {
        r += dr;
        double r_exp_six = r*r*r*r*r*r;
        double sigma_over_r = sigma_exp_six / r_exp_six;
        u = 4.0 * eps * sigma_over_r * (sigma_over_r - 1.0);

        file << r << " " << u << "\n";

    }

    file.close();
}
int main() {
    std::vector<Particle<3>> particles = generate_particles_vector(2);
    lennard_jones_potential(particles);
}