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
    std::string file_path = source_path.substr(0, last_separator + 1) + "dat_files/lennard_jones.dat";

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