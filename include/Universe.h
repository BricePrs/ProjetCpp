//
// Created by brice on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_UNIVERSE_H
#define TP_PERESB_HASSANH_UNIVERSE_H
#include <array>
#include "Particle.h"
#include "unordered_dense.h"

class Cell {
public:
    Cell();

    void place(uint32_t id);
    unordered_dense::map<uint32_t> get_particles();
    void empty();
private:
    std::vector<uint32_t> _particles;
};

template <unsigned int n>
class Universe {
public:
    typedef std::array<int32_t, n> CellID;

    Universe(Vector<n> bottom_left, Vector<n> top_right, double cell_size);

    void add(Vector<n> position, Vector<n> velocity, double mass, Category category);
    void random_fill(uint32_t particle_count);

    void simulate_without_grid(double t_end, double dt, bool gravitational,bool lennard_jones);
    void simulate_with_grid(double t_end, double dt, bool gravitational,bool lennard_jones);

    void save_state(const std::string &filename);

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
    void update_strengths_without_grid(bool gravitational,bool lennard_jones);
    void update_strengths_with_grid(bool gravitational,bool lennard_jones);
    void reset_forces();
};




#include "Universe.txx"

#endif //TP_PERESB_HASSANH_UNIVERSE_H
