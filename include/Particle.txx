//
// Created by helen on 23/02/23.
//
#include <list>
#include <random>
#include <iostream>
#include "Particle.h"

template <unsigned int n>
Particle<n>::Particle(uint32_t id, Vector<n> pos, Vector<n> speed, Vector<n> strength, double mass, Category category) {
    this->id = id;
    this->pos = pos;
    this->speed = speed;
    this->strength = strength;
    this->mass = mass;
    this->category = category;
}


template <unsigned int n>
Particle<n> Particle<n>::random(uint32_t id) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    return Particle(
            id,
            Vector<n>::random_in_unit_pos_cube(),
            Vector<n>::random_in_unit_pos_cube(),
            Vector<n>::random_in_unit_pos_cube(),
            dist(mt),
            static_cast<Category>(rand() % 3) // TODO : avoid rand
            );
}

