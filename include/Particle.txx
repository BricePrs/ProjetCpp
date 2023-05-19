#include <random>
#include <iostream>
#include "Particle.h"

template <unsigned int n>
Particle<n>::Particle(uint32_t id, Vector<n> pos, Vector<n> speed, double mass, Category category) :
    _id(id), _position(pos), _speed(speed), _mass(mass), _category(category), _force(Vector<n>::zero()) {}


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
inline double Particle<n>::compute_lennard_jones_intensity(double dist_sq) {
        double one_over_rij_sq = 1./dist_sq;
        double one_over_r_ij_exp_six = one_over_rij_sq * one_over_rij_sq * one_over_rij_sq;
        double sigma_ov_r_ij = sigma_exp_six * one_over_r_ij_exp_six;
        return (24.0 * eps * one_over_rij_sq * (sigma_ov_r_ij) * (1.0 - 2.0 * sigma_ov_r_ij));
}

template<unsigned int n>
double Particle<n>::kinetic_energy() {
    return 0.5*_mass*_speed.sq_length();
}

template<unsigned int n>
void Particle<n>::apply_gravity() {
    Vector up = Vector<n>::zero();
    up[1] = 1.;
    apply_force(CST_G * _mass);
}

template<unsigned int n>
inline void Particle<n>::compute_forces(Particle &a, Particle &b, bool gravitational, bool lennard_jones) {
    double F_length = 0.;

    Vector<n> R_ij(b.get_pos() - a.get_pos());
    double r_ij_sq = R_ij.sq_length();

    // interactions (Lennard-Jones)
    if (lennard_jones) {
        if (r_ij_sq <= r_cut_sq) {
            F_length += compute_lennard_jones_intensity(r_ij_sq);
        }
    }

    // gravitational strength
    if (gravitational) {
        F_length += (a.get_mass() * b.get_mass() / r_ij_sq / sqrt(r_ij_sq));
    }

    Vector F_i = F_length * R_ij;
    a.apply_force(F_i);
    b.apply_force(-F_i);
}

