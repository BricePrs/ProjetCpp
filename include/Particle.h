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
    Particle(uint32_t id, Vector<n> pos, Vector<n> speed, Vector<n> strength, double mass, Category category);
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
        return this->strength;
    }

    double get_mass() {
        return this->mass;
    }

    Category get_category() {
        return this->category;
    }

    void set_pos(Vector<n> &new_pos) {
        this->pos = new_pos;
    }

    void set_speed(Vector<n> &new_speed) {
        this->speed = new_speed;
    }

    void set_strength(Vector<n> &new_strength) {
        this->strength = new_strength;
    }


    bool operator<(const Particle &p) const {
        return id < p.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Particle& p) {
        os << "Particle : { "
           << " id: " << p.id
           << " , pos : " << p.pos
           << " , speed : " << p.speed
           << " , strength : " << p.strength
           << " , mass : " << p.mass
           << " , category : " << p.category << "\n";
        return os;
    }

private:
    uint32_t id;
    Vector<n> pos;
    Vector<n> speed;
    Vector<n> strength;
    double mass;
    Category category;

    // TODO : Is it better ?
    // static uint32_t particle_count;

};

#include "Particle.txx"



#endif //TP_PERESB_HASSANH_PARTICLE_H
