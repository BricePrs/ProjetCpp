//
// Created by brice on 13/04/23.
//

#ifndef TP_PERESB_HASSANH_UNIVERSE_H
#define TP_PERESB_HASSANH_UNIVERSE_H
#include <array>
#include "Particle.h"

class Cell {
public:
    Cell();

    void place(uint32_t id);
    std::vector<uint32_t> get_particles();
    void empty();

    std::vector<int32_t> _neightbours;
private:
    std::vector<uint32_t> _particles;
};

template <unsigned int n>
class Universe {
public:
    Universe(Vector<n> bottom_left, Vector<n> top_right, double cell_size);

    void add(Vector<n> position, Vector<n> velocity, double mass, Category category);
    void random_fill(uint32_t particle_count);

    void simulate(double t_end, double dt, bool gravitational, bool lennard_jones, bool use_grid, uint32_t save_each);

    void save_state(const std::string &filename);

private:
    static const std::array<int, n> neighbour_cell_offsets;

    std::vector<Particle<n>> _particles;

    // Simulation Constraints
    Vector<n> _bottom_left;
    Vector<n> _top_right;

    // Grid characteristics
    double _cell_size;
    std::vector<Cell> _cells;
    std::array<int32_t, n> _grid_dimensions;

    void init_grid(std::array<int32_t, n> size);

    // Cell utility functions
    int32_t get_cell_id(Vector<n> position);
    Cell get_cell_with_id(int32_t id);
    std::vector<int32_t> compute_cell_neighbours(int32_t id);
    std::vector<int32_t> get_cell_upper_neighbours(uint32_t dimension, int32_t id);
    std::vector<int32_t> get_cell_lower_neighbours(uint32_t dimension, int32_t id);

    void empty_grid();
    void place_particles();

    // Simulation utility functions
    void update_strengths_without_grid(bool gravitational,bool lennard_jones);
    void update_strengths_with_grid(bool gravitational,bool lennard_jones);
    void reset_forces();

};




#include "Universe.txx"

#endif //TP_PERESB_HASSANH_UNIVERSE_H
