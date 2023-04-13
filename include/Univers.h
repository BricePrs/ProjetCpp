//
// Created by brice on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_UNIVERS_H
#define TP_PERESB_HASSANH_UNIVERS_H


#include <array>
#include "particle.h"

class Univers {
public:
    Univers(uint32_t particle_count);

    void stromer_verlet(double t_end, double dt);

private:
    std::vector<Particle> particles;

    void update_strengths();
};


#endif //TP_PERESB_HASSANH_UNIVERS_H
