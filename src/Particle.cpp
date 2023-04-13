//
// Created by helen on 23/02/23.
//
#include <list>
#include <random>
#include <iostream>
#include "Particle.h"

Particle::Particle(uint32_t id, Vector<3> pos, Vector<3> speed, Vector<3> strength, double mass, Category category) {
    this->id = id;
    this->pos = pos;
    this->speed = speed;
    this->strength = strength;
    this->mass = mass;
    this->category = category;
}


std::ostream &operator<<(std::ostream &os, const Particle &p) {
    os << "Particle : { "
       << " id: " << p.id
       << " , pos : " << p.pos
       << " , speed : " << p.speed
       << " , strength : " << p.strength
       << " , mass : " << p.mass
       << " , category : " << p.category << "\n";
    return os;
}

Particle Particle::random(uint32_t id) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    return Particle(
            id,
            Vector<3>::random_in_unit_pos_cube(),
            Vector<3>::random_in_unit_pos_cube(),
            Vector<3>::random_in_unit_pos_cube(),
            dist(mt),
            static_cast<Category>(rand() % 3) // TODO : avoid rand
            );
}

