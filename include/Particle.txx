//
// Created by helen on 23/02/23.
//
#include <list>
#include <random>
#include <iostream>
#include "Particle.h"

template <unsigned int n>
Particle<n>::Particle(uint32_t id, Vector<n> pos, Vector<n> speed, double mass, Category category) :
    _id(id), _position(pos), _speed(speed), _mass(mass), _category(category), _force(Vector<n>::zero())
{
}


template <unsigned int n>
Particle<n> Particle<n>::random(uint32_t id) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<double> dist(0.1, 1.0);

    return Particle(
            id,
            Vector<n>::random_in_unit_pos_cube(),
            Vector<n>::random_in_unit_pos_cube(),
            dist(mt),
            static_cast<Category>(rand() % 3) // TODO : avoid rand
            );
}

template<unsigned int n>
void Particle<n>::compute_forces(Particle &a, Particle &b, bool gravitational, bool lennard_jones) {
    if (a == b) return;

    Vector<n> F_i;

    Vector<n> R_ij = b.get_pos() - a.get_pos();
    double r_ij = R_ij.length();
    double r_ij_sq = r_ij * r_ij;

    // gravitational strength
    if (gravitational) {
        F_i = (a.get_mass() * b.get_mass() / r_ij_sq / r_ij) * R_ij;
    }

    if (lennard_jones) {
        if (r_ij <= r_cut) {
            double r_ij_exp_six = r_ij_sq * r_ij_sq * r_ij_sq;
            double sigma_ov_r_ij = sigma_exp_six / r_ij_exp_six;
            // interactions (Lennard-Jones)
            F_i = 24.0 * eps * 1 / r_ij_sq * (sigma_ov_r_ij) * (1.0 - 2.0 * sigma_ov_r_ij) * R_ij;
        }
    }

    a.set_force(a.get_strength() + F_i);
    b.set_force(b.get_strength() + -F_i);
}

