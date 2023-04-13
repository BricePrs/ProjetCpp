//
// Created by brice on 13/04/23.
//

#include <fstream>
#include "Univers.h"

Univers::Univers(uint32_t particle_count) {
    this->particles.reserve(particle_count);
    static uint32_t id = 0;
    for (uint32_t particle_id = id; particle_id < id + particle_count; particle_id++) {
        this->particles.push_back(Particle::random(particle_id));
    }
    id += particle_count;
}

void Univers::update_strengths() {
    int nb_particles = this->particles.size();
    Vector3 F_i;
    Vector3 R_ij;
    double r_ij;
    for (uint32_t i = 0; i<nb_particles; i++) {
        F_i = Vector3();
        for (uint32_t j = 0; j < nb_particles; j++) {
            if (j != i) {
                R_ij = this->particles[j].get_pos() - this->particles[i].get_pos();
                r_ij = R_ij.length();
                F_i += (this->particles[i].get_mass() * this->particles[j].get_mass() / (r_ij*r_ij)) * R_ij;
            }
        }
        this->particles[i].set_strength(F_i);
    }
}

void Univers::stromer_verlet(double t_end, double dt) {

    std::string source_path = __FILE__;
    size_t last_separator = source_path.find_last_of("/\\");
    std::string file_path = source_path.substr(0, last_separator + 1) + "stromer_verlet.txt";

    std::ofstream file(file_path);
    double t = 0.0;

    uint32_t nb_particles = this->particles.size();

    std::vector<Vector3> F_old(nb_particles);

    // initialization of particles strengths
    update_strengths();

    while (t<t_end) {
        t+=dt;

        std::string file_line = std::to_string(t) + " ";

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle &p = this->particles[i];
            Vector3 new_pos = p.get_pos() + dt * (p.get_speed() + (0.5 / p.get_mass()) * p.get_speed() * dt);
            p.set_pos(new_pos);
            F_old[i] = p.get_strength();
        }

        update_strengths();

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle p = this->particles[i];
            Vector3 new_speed = p.get_speed() + dt * (0.5 / p.get_mass()) * (p.get_strength() + F_old[i]);
            p.set_speed(new_speed);

            // adding new_pos of each particle to file
            file_line += p.get_pos().to_string() + " ";
        }
        file_line += "\n";
        file << file_line;
    }
    file.close();
}
