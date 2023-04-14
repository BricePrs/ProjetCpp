//
// Created by brice on 13/04/23.
//

#include "Universe.h"

template <unsigned int n>
Universe<n>::Universe(uint32_t particle_count) {
    this->particles.reserve(particle_count);
    static uint32_t id = 0;
    for (uint32_t particle_id = id; particle_id < id + particle_count; particle_id++) {
        this->particles.push_back(Particle<n>::random(particle_id));
    }
    id += particle_count;
}

template <unsigned int n>
void Universe<n>::update_strengths() {
    int nb_particles = this->particles.size();
    Vector<n> F_i;
    Vector<n> R_ij;
    double r_ij;
    double r_ij_sq;
    double r_cut = 2.5;

    // parameters for Lennard Jones' potential
    double eps = 1.0;
    double sigma = 1.0;
    double sigma_exp_six = sigma * sigma * sigma * sigma * sigma * sigma;

    for (uint32_t i = 0; i<nb_particles; i++) {
        F_i = Vector<n>();
        for (uint32_t j = 0; j < nb_particles; j++) {
            if (j != i) {
                R_ij = this->particles[j].get_pos() - this->particles[i].get_pos();
                r_ij = R_ij.length();
                r_ij_sq = r_ij * r_ij;

                // gravitational strength
                F_i += (this->particles[i].get_mass() * this->particles[j].get_mass() / r_ij_sq) * R_ij;

                if (j != 1 && r_ij <= r_cut) {
                    double r_ij_exp_six = r_ij_sq * r_ij_sq * r_ij_sq;
                    double sigma_ov_r_ij = sigma_exp_six/r_ij_exp_six;
                    // interactions (Lennard-Jones)
                    F_i += 24.0 * eps * 1/r_ij_sq * (sigma_ov_r_ij) * (1.0 - 2.0 * sigma_ov_r_ij) * R_ij;
                }
            }
        }
        this->particles[i].set_strength(F_i);
    }
}

/**
 * Simulation of particles using the Stormer Verlet algorithm
 * @param t_end : maximum time of the simulation
 * @param dt : time step
 */
template <unsigned int n>
void Universe<n>::simulate(double t_end, double dt) {

    double t = 0.0;

    uint32_t nb_particles = this->particles.size();

    std::vector<Vector<n>> F_old(nb_particles);

    // initialization of particles strengths
    update_strengths();

    while (t<t_end) {
        t+=dt;

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle<n> &p = this->particles[i];
            Vector<n> new_pos = p.get_pos() + dt * (p.get_speed() + (0.5 / p.get_mass()) * p.get_speed() * dt);
            p.set_pos(new_pos);
            F_old[i] = p.get_strength();
        }

        update_strengths();

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle p = this->particles[i];
            Vector<n> new_speed = p.get_speed() + dt * (0.5 / p.get_mass()) * (p.get_strength() + F_old[i]);
            p.set_speed(new_speed);
        }
    }
}
