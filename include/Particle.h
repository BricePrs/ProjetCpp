//
// Created by helen on 23/02/23.
//

#include <random>
#include <iostream>
#include "Vector.h"

#ifndef PARTICLE_H
#define PARTICLE_H

enum Category {
    ELECTRON [[maybe_unused]],
    PROTON [[maybe_unused]],
    NEUTRON [[maybe_unused]],
};

template <unsigned int n>
class Particle {
public:
    Particle(uint32_t id, Vector<n> pos, Vector<n> speed, double mass, Category category);
    Particle() = default;
    Particle(const Particle &p) = default;

    static Particle random(uint32_t id);

    uint32_t get_id() {
        return this->id;
    }

    Vector<n> get_pos() {
        return this->pos;
    }

    Vector<n> get_speed() {
        return this->speed;
    }

    Vector<n> get_strength() {
        return this->force;
    }

    double get_mass() {
        return this->mass;
    }

    Category get_category() {
        return this->category;
    }

    inline void set_pos(const Vector<n> &new_pos) {
        this->pos = new_pos;
    }

    inline void set_speed(const Vector<n> &new_speed) {
        this->speed = new_speed;
    }

    inline void set_strength(const Vector<n> &new_strength) {
        this->force = new_strength;
    }


    bool operator<(const Particle &p) const {
        return id < p.id;
    }

    bool operator==(const Particle &p) const {
        return id == p.id;
    }

    bool operator!=(const Particle &p) const {
        return id != p.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Particle& p) {
        os << "Particle : { "
           << " id: " << p.id
           << " , pos : " << p.pos
           << " , speed : " << p.speed
           << " , strength : " << p.force
           << " , mass : " << p.mass
           << " , category : " << p.category << "\n";
        return os;
    }

    static void compute_forces(Particle &a, Particle &b, bool gravitational, bool lennard_jones);

private:
    inline static double r_cut = 2.5;

    // parameters for Lennard Jones' potential
    inline static double eps = 1.0;
    inline static double sigma = 1.0;
    inline static double sigma_exp_six = pow(sigma, 6);

    uint32_t id;
    Vector<n> pos;
    Vector<n> speed;
    Vector<n> force;
    double mass;
    Category category;

    // TODO : Is it better ?
    // static uint32_t particle_count;

};



#include "Particle.txx"



#endif //TP_PERESB_HASSANH_PARTICLE_H
