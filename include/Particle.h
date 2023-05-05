/**
    @file Particle.h
    @brief Defines a Particle class representing a particle in an n-dimensional world, described by its position, speed, mass, and category.
    @author helen
    @date 23/02/23
    */

#ifndef PARTICLE_H
#define PARTICLE_H

#include <random>
#include <iostream>
#include "Vector.h"

/**
    @enum Category
    @brief Represents the type of a particle.
    */
enum Category {
    ELECTRON, ///< Represents an electron particle.
    PROTON, ///< Represents a proton particle.
    NEUTRON ///< Represents a neutron particle.
};

/**
    @class Particle

    @brief Represents a particle in an n-dimensional world, described by its position, speed, mass, and category.

    @tparam n The dimension of the world in which the particle exists.
    */
template <unsigned int n>
class Particle {
public:
    /*
        @brief Constructs a new Particle object with the given ID, position, speed, mass, and category.
        @param id The ID of the particle.
        @param pos The position of the particle in the n-dimensional world.
        @param speed The speed of the particle in the n-dimensional world.
        @param mass The mass of the particle.
        @param category The category (type) of the particle.
        */
    Particle(uint32_t id, Vector<n> pos, Vector<n> speed, double mass, Category category);

    /**
        @brief Constructs a default Particle object.
        */
    Particle() = default;

    /**
        @brief Constructs a Particle object by copying another Particle object.
        @param p The Particle object to copy.
        */
    Particle(const Particle &p) = default;

    /**
        @brief Generates a random Particle object with the given ID.
        @param id The ID of the particle.
        @return A new Particle object with random position, speed, mass, and category.
        */
    static Particle random(uint32_t id);

    /**
        @brief Gets the ID of the particle.
        @return The ID of the particle.
        */
    uint32_t get_id() {
        return this->_id;
    }

    /**
        @brief Gets the position of the particle in the n-dimensional world.
        @return The position of the particle.
        */
    const Vector<n> &get_pos() {
        return this->_position;
    }

    /**
        @brief Gets the speed of the particle in the n-dimensional world.
        @return The speed of the particle.
        */
    const Vector<n> &get_speed() {
        return this->_speed;
    }

    /**
        @brief Gets the force acting on the particle in the n-dimensional world.
        @return The force acting on the particle.
        */
    const Vector<n> &get_strength() {
        return this->_force;
    }

    /**
        @brief Gets the mass of the particle.
        @return The mass of the particle.
        */
    const double &get_mass() {
        return this->_mass;
    }

    /**
        @brief Gets the category (type) of the particle.
        @return The category (type) of the particle.
        */
    const Category &get_category() {
        return this->_category;
    }

    /**
        @brief Sets the position of the particle in the n-dimensional world.
        @param new_pos The new position of the particle.
        */
    inline void set_pos(const Vector<n> &new_pos) {
        this->_position = new_pos;
    }

    /**
      * @brief Sets the speed of the particle in the n-dimensional world.
      * @param new_speed The new speed
      */
    inline void set_speed(const Vector<n> &new_speed) {
        this->_speed = new_speed;
    }

    inline void set_force(const Vector<n> &new_force) {
        this->_force = new_force;
    }

    inline void apply_force(const Vector<n> &new_force) {
        this->_force += new_force;
    }

    bool operator<(const Particle &p) const {
        return _id < p._id;
    }

    bool operator==(const Particle &p) const {
        return _id == p._id;
    }

    bool operator!=(const Particle &p) const {
        return _id != p._id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Particle& p) {
        os << "Particle : { "
           << " id: " << p._id
           << " , pos : " << p._position
           << " , speed : " << p._speed
           << " , strength : " << p._force
           << " , mass : " << p._mass
           << " , category : " << p._category << "\n";
        return os;
    }
    /**
      * @brief Compute the force that each particule exert
      * on the other and add it to the particle strength field
      * @param a Particule a
      * @param b Particule a
      * @param gravitational should the gravitationnal force be taken into account
      * @param lennard_jones should the lennard_jones potential related force be taken into account
      */
    static void compute_forces(Particle &a, Particle &b, bool gravitational, bool lennard_jones);

private:
    inline static double r_cut_sq = 2.5*2.5;

    // parameters for Lennard Jones' potential
    inline static double eps = 5.0;
    inline static double sigma = 1.0;
    inline static double sigma_exp_six = pow(sigma, 6);

    uint32_t _id{};
    Vector<n> _position;
    Vector<n> _speed;
    Vector<n> _force;
    double _mass{};
    Category _category;

};


#include "Particle.txx"

#endif //TP_PERESB_HASSANH_PARTICLE_H
