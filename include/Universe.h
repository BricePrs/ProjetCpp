//
// Created by brice on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_UNIVERSE_H
#define TP_PERESB_HASSANH_UNIVERSE_H
#include <array>
#include "Particle.h"

class Cell {
public:
    void place(uint32_t id);
    std::vector<uint32_t> get_particles();
    void empty();
private:
    std::vector<uint32_t> _particles;
};

template <unsigned int n>
class Universe {
public:
    typedef std::array<int32_t, n> CellID;

    Universe(uint32_t particle_count, Vector<n> bottom_left, Vector<n> top_right, double cell_size);

    void simulate_without_grid(double t_end, double dt);
    void simulate_with_grid(double t_end, double dt);

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

    CellID get_cell_id(Vector<n> position);
    CellID get_cell_id(CellID id);
    Cell get_cell_with_id(CellID id);
    std::vector<CellID> get_cell_neighbours(CellID id);
    uint32_t get_cell_linear_id(Universe::CellID id);
    CellID get_cell_dimentional_id(uint32_t id);
    void empty_grid();

    void place_particles();
    void update_strengths_without_grid();
    void update_strengths_with_grid();
};




#include "Universe.txx"

#endif //TP_PERESB_HASSANH_UNIVERSE_H
