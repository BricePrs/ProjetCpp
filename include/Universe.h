//
// Created by brice on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_UNIVERSE_H
#define TP_PERESB_HASSANH_UNIVERSE_H
#include <array>
#include "Particle.h"


template <unsigned int n>

class Universe {
public:
    Universe(uint32_t particle_count);

    void simulate(double t_end, double dt);

private:
    std::vector<Particle<n>> particles;

    void update_strengths();
};

#include "Universe.txx"

#endif //TP_PERESB_HASSANH_UNIVERSE_H
