//
// Created by helen on 23/02/23.
//

#include <random>
#include <iostream>
#include <list>
#include <set>
#include <deque>
#include <vector>

#ifndef TP2_PARTICLE_H
#define TP2_PARTICLE_H

enum Category {
    ELECTRON,
    PROTON,
    NEUTRON,
};
enum DataStructure {
    SET,
    LIST,
    VECTOR,
    QUEUE,
};
struct Vector3 {
    double x;
    double y;
    double z;
};

class Particle {
public:
    Particle(uint32_t id, Vector3 pos, Vector3 speed, Vector3 strength, double mass, Category category);
    Particle() = default;
    Particle(const Particle &p) = default;

    uint32_t get_id() {
        return this->id;
    }

    Vector3 get_pos() {
        return this->pos;
    }

    Vector3 get_speed() {
        return this->speed;
    }

    Vector3 get_strength() {
        return this->strength;
    }

    double get_mass() {
        return this->mass;
    }

    Category get_category() {
        return this->category;
    }

    void set_pos(Vector3 &new_pos) {
        this->pos = new_pos;
    }

    void set_speed(Vector3 &new_speed) {
        this->speed = new_speed;
    }

    void set_strength(Vector3 &new_strength) {
        this->strength = new_strength;
    }


    bool operator<(const Particle &p) const {
        return id < p.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Particle& p);

private:
    uint32_t id;
    Vector3 pos;
    Vector3 speed;
    Vector3 strength;
    double mass;
    Category category;
};



#endif //TP2_PARTICLE_H
