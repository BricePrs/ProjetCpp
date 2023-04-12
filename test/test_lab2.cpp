//
// Created by helen on 23/02/23.
//
#include "particle.h"
#include <chrono>
#include <fstream>
auto new_random_vec3(std::mt19937 &gen, std::uniform_real_distribution<double> &distribution) -> Vector3 {
    return Vector3{distribution(gen), distribution(gen), distribution(gen)};
}

auto new_random_double(std::mt19937 &gen, std::uniform_real_distribution<double> &distribution) -> double {
    return distribution(gen);
}


std::list<Particle> generate_particles_list(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-500.0, 500.0);

    // particle set creations
    std::list<Particle> particles_list;
    std::list<Particle>::iterator particles_it = particles_list.begin();

    for (uint i = 0; i < nb_particles; i++ ) {
        Particle new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_list.insert(particles_it, new_part);
    }
    return particles_list;
}

std::deque<Particle> generate_particles_queue(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-500.0, 500.0);

    // particle set creations
    std::deque<Particle> particles_queue;

    for (uint i = 0; i < nb_particles; i++ ) {
        Particle new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_queue.push_back(new_part);
    }
    return particles_queue;
}

std::set<Particle> generate_particles_set(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-500.0, 500.0);

    // particle set creations
    std::set<Particle> particles_set;
    for (uint i = 0; i < nb_particles; i++ ) {
        Particle new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_set.insert(new_part);
    }
    return particles_set;
}

std::vector<Particle> generate_particles_vector(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-500.0, 500.0);

    // particle set creations
    std::vector<Particle> particles_vector(nb_particles);

    for (uint i = 0; i < nb_particles; i++ ) {
        Particle new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_vector[i] = new_part;
    }
    return particles_vector;
}


void run(std::list<uint32_t> particles_sizes) {
    std::chrono::duration<double> elapsed_seconds_set, elapsed_seconds_list, elapsed_seconds_queue, elapsed_seconds_vector;
    for (auto size: particles_sizes) {
        auto start = std::chrono::steady_clock::now();
        std::list<Particle> particles_list = generate_particles_list(size);
        elapsed_seconds_list = std::chrono::steady_clock::now() - start;

        start = std::chrono::steady_clock::now();
        std::set<Particle> particles_set = generate_particles_set(size);
        elapsed_seconds_set = std::chrono::steady_clock::now() - start;

        start = std::chrono::steady_clock::now();
        std::vector<Particle> particles_vector = generate_particles_vector(size);
        elapsed_seconds_vector = std::chrono::steady_clock::now() - start;

        start = std::chrono::steady_clock::now();
        std::deque<Particle> particles_deque = generate_particles_queue(size);
        elapsed_seconds_queue = std::chrono::steady_clock::now() - start;


        // print time elapsed
        std::cout << "Time elapsed for a collection of particles of size " << size
        << " ===> LIST : " << elapsed_seconds_list.count()
        << " / SET : " << elapsed_seconds_set.count()
        << " / VECTOR : " << elapsed_seconds_vector.count()
        << " / QUEUE : " << elapsed_seconds_queue.count()
        << "\n" ;
    }
}


void data_structures_comparison() {
    std::list<uint32_t> sizes = {64, 128, 256, 512, 1028, 2048};
    run(sizes);
}

/*
void update_strengths(std::vector<Particle> &particles) {
    int nb_particles = particles.size();
    Vector3 F_i;
    Vector3 F_ij;
    Vector3 R_ij;
    double r_ij;
    for (uint32_t i = 0; i<nb_particles; i++) {
        F_i = = {0.0, 0.0, 0.0};
        for (uint32_t j = 0; j < nb_particles; j++) {
            if (j != i) {
                R_ij = particles[j].get_pos() - particles[i].get_pos();
                r_ij = R_ij.length();
                F_i += (particles[i].get_mass() * particles[j].get_mass() / (r_ij*r_ij)) * R_ij;
            }
        }
        particles[i].set_strength(F_i);
    }
}


void stromer_verlet(std::vector<Particle> &particles, double t_end, double dt) {
    std::ofstream file("stromer_verlet.txt");

    double t = 0.0;

    uint32_t nb_particles = particles.size();

    std::vector<Vector3> F_old(nb_particles);

    // initialization of particles strengths
    update_strengths(particles);

    while (t<t_end) {
        t+=dt;

        std::string file_line = std::to_string(t);

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle p = particles[i];
            Vector3 new_pos = p.get_pos() + dt * (p.get_speed() + (0.5 / p.get_mass()) * p.get_speed() * dt);
            p.set_pos(new_pos);
            F_old[i] = p.get_strength();
        }

        update_strengths(particles);

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle p = particles[i];
            Vector3 new_speed = p.get_speed() + dt * (0.5 / p.get_mass()) * (p.get_strength() + F_old[i]);
            p.set_speed(new_speed);

            // adding new_pos of each particle to file
            file_line += p.get_pos() + " ";

        }
        file_line += "\n";
        file << file_line;
    }
}
*/


int main() {
    // comparison of particles
    data_structures_comparison();

    // current particles system is composed of the Sun, Earth, Jupiter, Haley comet (4 particles)
    std::vector<Particle> particles = generate_particles_vector(4);
    //stromer_verlet(particles, 465.5, 0.015);


}