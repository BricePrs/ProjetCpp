/**
 * @file Universe.h
 * @brief Definition of the Universe class.
 */

#ifndef TP_PERESB_HASSANH_UNIVERSE_H
#define TP_PERESB_HASSANH_UNIVERSE_H

#include <array>
#include <unordered_set>
#include <set>
#include <thread>

#include "emhash_set8.h"
#include "ankerl_hash.h"
#include "Particle.h"

enum BoundaryBehaviour {
    Reflexive,
    Absorption,
    Periodic,
};

/**
 * @class Cell
 * @brief Class representing a cell in the grid.
 */
class Cell {
public:
    /**
     * @brief Default constructor.
     */
    Cell();

    /**
     * @brief Place a particle in the cell.
     * @param id Particle ID.
     */
    void place(uint32_t id);

    /**
     * @brief Get the IDs of all particles in the cell.
     * @return Vector of particle IDs.
     */
    std::vector<uint32_t> &get_particles();

    /**
     * @brief Remove all particles from the cell.
     */
    void empty();

    void lock();
    void unlock();

    std::vector<int32_t> _neightbours; ///< Indices of neighbouring cells.
private:
    std::vector<uint32_t> _particles; ///< IDs of particles in the cell.
    pthread_mutex_t mutex;
};

/**
 * @class Universe
 * @brief Class representing the simulation universe.
 */
template <unsigned int n>
class Universe {
public:
    Universe(Vector<n> bottom_left, Vector<n> top_right, double cell_size, BoundaryBehaviour boundary_behaviour);

    void add(Vector<n> position, Vector<n> velocity, double mass, Category category);
    int add_packed_particles(Vector<n> bottom_left, Vector<n> top_right, Vector<n> velocity, double mass, Category category, Vector<n> particle_count);
    void random_fill(uint32_t particle_count);

    void simulate(double t_end, double dt, bool gravitational, bool lennard_jones, bool use_grid, uint32_t save_each, uint32_t threads);

    void save_state(const std::string &filename);

private:
    typedef emhash8::HashSet<uint32_t, ankerl::unordered_dense::hash<Particle<n>>> FastHashSet;

    std::array<int, n> _neighbour_cell_offsets; ///< the offset to get the neightbour of a cell for each dimension

    std::vector<Particle<n>> _particles; ///< The universe particles

    // Simulation Constraints
    BoundaryBehaviour _boundary_behaviour; /// Particule behaviour if outside of boundaries
    Vector<n> _bottom_left; ///< Particule postion can't go below this
    Vector<n> _top_right;///< Particule postion can't go above this
    Vector<n> _center;
    Vector<n> _width;

    // Grid characteristics
    double _cell_size; ///< The size of each grid cell
    uint32_t _cells_count; ///< The number of cells
    std::vector<Cell> _cells; ///< The array of cells
    std::array<int32_t, n> _grid_dimensions; ///< The dimensions of the grid

    /// @brief Initialize the universe grid with the dimensions `size`
    /// @param size the dimensions of the grid
    void init_grid(std::array<int32_t, n> size);


    /*
     * Cell utility functions
     */

    /// @brief Compute the id of the cell that contains `position`
    /// @param postion
    int32_t get_cell_id(Vector<n> position);

    /// @brief Getter for the cell with id `id`
    /// @param id
    Cell get_cell_with_id(int32_t id);

    /// @brief Compute the neightbour cell of cell with id `id`
    /// @param id
    std::vector<int32_t> compute_cell_neighbours(int32_t id);

    /// @brief Empty the grid
    void empty_grid();

    /// @brief place all the universe's particles in their coresponding cell
    void place_particles();

    /// @brief move all the universe's particles in their coresponding cell
    void update_particles_cells();

    /*
     * Simulation utility functions
     */

    /// @brief Update all the particles forces field without using the grid
    /// @param gravitational should the gravitational force be taken into account
    /// @param lennard_jones should the lennard_jones potential force be taken into account
    void update_forces_without_grid(bool gravitational, bool lennard_jones);

    /// @brief Update all the particles forces field using the grid
    /// @param gravitational should the gravitational force be taken into account
    /// @param lennard_jones should the lennard_jones potential force be taken into account
    void update_forces_with_grid(bool gravitational, bool lennard_jones, uint32_t threads);

    /// @brief Update all the particles forces field using the grid
    /// @param gravitational should the gravitational force be taken into account
    /// @param lennard_jones should the lennard_jones potential force be taken into account
    /// @param grid_lb grid lower bound index (included)
    /// @param grid_lb grid upper bound index (not included)
    void update_forces_with_grid_range(bool gravitational, bool lennard_jones, int32_t grid_lb, int32_t grid_ub);

    /// @brief Reset all particles forces to zero
    void reset_forces();

};


#include "Universe.txx"

#endif //TP_PERESB_HASSANH_UNIVERSE_H
