#include "Particle.h"
#include <chrono>
#include <fstream>
#include <deque>
#include <set>
#include <list>

auto new_random_vec3(std::mt19937 &gen, std::uniform_real_distribution<double> &distribution) -> Vector<3> {
    return Vector<3>{distribution(gen), distribution(gen), distribution(gen)};
}

auto new_random_double(std::mt19937 &gen, std::uniform_real_distribution<double> &distribution) -> double {
    return distribution(gen);
}


std::list<Particle<3>> generate_particles_list(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-500.0, 500.0);

    // particle set creations
    std::list<Particle<3>> particles_list;
    std::list<Particle<3>>::iterator particles_it = particles_list.begin();

    for (uint i = 0; i < nb_particles; i++ ) {
        Particle<3> new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_list.insert(particles_it, new_part);
    }
    return particles_list;
}

std::deque<Particle<3>> generate_particles_queue(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-500.0, 500.0);

    // particle set creations
    std::deque<Particle<3>> particles_queue;

    for (uint i = 0; i < nb_particles; i++ ) {
        Particle new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_queue.push_back(new_part);
    }
    return particles_queue;
}

std::set<Particle<3>> generate_particles_set(uint32_t nb_particles) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-50000.0, 50000.0);

    // particle set creations
    std::set<Particle<3>> particles_set;
    for (uint i = 0; i < nb_particles; i++ ) {
        Particle new_part = Particle(i, new_random_vec3(mt, dist), new_random_vec3(mt, dist),
                                     new_random_double(mt, dist), static_cast<Category>(rand() % 3));
        particles_set.insert(new_part);
    }
    return particles_set;
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


void run(std::list<uint32_t> particles_sizes) {
    std::chrono::duration<double> elapsed_seconds_set, elapsed_seconds_list, elapsed_seconds_queue, elapsed_seconds_vector;
    for (auto size: particles_sizes) {
        auto start = std::chrono::steady_clock::now();
        std::list<Particle<3>> particles_list = generate_particles_list(size);
        elapsed_seconds_list = std::chrono::steady_clock::now() - start;

        start = std::chrono::steady_clock::now();
        std::set<Particle<3>> particles_set = generate_particles_set(size);
        elapsed_seconds_set = std::chrono::steady_clock::now() - start;

        start = std::chrono::steady_clock::now();
        std::vector<Particle<3>> particles_vector = generate_particles_vector(size);
        elapsed_seconds_vector = std::chrono::steady_clock::now() - start;

        start = std::chrono::steady_clock::now();
        std::deque<Particle<3>> particles_deque = generate_particles_queue(size);
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

int main() {
    data_structures_comparison();
}