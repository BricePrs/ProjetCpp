//
// Created by helen on 23/02/23.
//
#include <list>
#include <random>
#include <iostream>
#include "particle.h"



Particle::Particle(uint32_t id, Vector3 pos, Vector3 speed, Vector3 strength, double mass, Category category) {
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
       << " , pos : " << p.pos.x << ", " << p.pos.y << ", " << p.pos.z
       << " , speed : " << p.speed.x << ", " << p.speed.y << ", " << p.speed.z
       << " , strength : " << p.strength.x << ", " << p.strength.y << ", " << p.strength.z
       << " , mass : " << p.mass
       << " , category : " << p.category << "\n";
    return os;
}

