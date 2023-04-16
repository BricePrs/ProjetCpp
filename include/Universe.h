//
// Created by brice on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_UNIVERSE_H
#define TP_PERESB_HASSANH_UNIVERSE_H
#include <array>
#include "Particle.h"

class Cell {
private:
    std::vector<uint32_t> particles;
};

template <unsigned int n>
class Universe {
public:
    typedef std::array<int32_t, n> CellID;

    Universe(uint32_t particle_count, Vector<n> bottom_left, Vector<n> top_right, double cell_size);

    void simulate(double t_end, double dt);

private:

    std::vector<Particle<n>> _particles;

    // Simulation Constraints
    Vector<n> _bottom_left;
    Vector<n> _top_right;

    // Grid characteristics
    double _cell_size;
    std::vector<Cell> _cells;
    CellID _grid_dimensions;

    void init_grid(CellID size);

    template<typename... Args>
    CellID get_cell_id(Args... args);
    CellID get_cell_id(Vector<n> position);
    Cell get_cell_with_id(CellID id);
    std::vector<CellID> get_cell_neighbours(CellID id);
    uint32_t get_cell_linear_id(Universe::CellID id);

    void place_particles();
    void update_strengths();
};

#include "Universe.txx"

#endif //TP_PERESB_HASSANH_UNIVERSE_H
