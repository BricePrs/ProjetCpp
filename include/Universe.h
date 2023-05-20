/**
 * @file Universe.h
 * @brief Definition of the Universe class.
 */

#ifndef TP_PERESB_HASSANH_UNIVERSE_H
#define TP_PERESB_HASSANH_UNIVERSE_H

#include <array>
#include <unordered_set>
#include <set>

#include "emhash_set8.h"
#include "ankerl_hash.h"

#include "Particle.h"
#include "Cell.h"
#include "Grid.h"

enum BoundaryBehaviour {
    Reflexive,
    ReflexivePotential,
    Absorption,
    Periodic,
};

struct SimulationSettings {

	bool                external_gravity                   = false;		    ///< Should the external gravity be applied
	bool                gravitational_interaction          = false;		    ///< Should the gravitational interaction be applied
	bool                lennard_jones_interaction          = false;		    ///< Should the Lennard-Jones interaction be applied
	double              goal_kinetic_energy                = -1;   		    ///< The kinetic energy goal set by the user to force the system's kinetic energy to this level every 1000 physics iterations
	double              physics_time_step                  = -1.;  		    ///< The time step used in the physics simulation
	double              physics_time_total                 = -1.;  		    ///< The total time for the physics simulation
	uint32_t            iter_count_until_save              = 0;    		    ///< The number of iterations until saving the simulation
	uint32_t            iter_count_until_balance_energy    = 1000;			///< The number of iterations until balancing the system's kinetic energy
	BoundaryBehaviour   boundary_behaviour                 = Absorption;	///< Particle behavior if outside of boundaries
};

template <unsigned int n>
struct SimulationConstraints {

    SimulationConstraints(Vector<n> bottom_left, Vector<n> top_right)
        : bottom_left(bottom_left), top_right(top_right), center((top_right+bottom_left)/2.), width((top_right-bottom_left)/2.) {};

	Vector<n>   bottom_left;	///< Particle position can't go below this
	Vector<n>   top_right;  	///< Particle position can't go above this
	Vector<n>   center;     	///< The center of the universe
	Vector<n>   width;      	///< The distance from the center to the universe's borders for each dimension
};


/**
 * @class Universe
 * @brief Class representing the simulation universe.
 */
template <unsigned int n>
class Universe {
public:

    Universe(SimulationConstraints<n> constraints, double cell_size);

    /*
     * Getter
     */
    /// @brief Returns the amount of particles inside the Universe.
    /// \return
    int get_particles_count() {
        return _particles.size();
    }

    void    add(Vector<n> position, Vector<n> velocity, double mass, Category category);
    int     add_packed_particles(Vector<n> bottom_left, Vector<n> top_right, Vector<n> velocity, double mass, Category category, Vector<n> particle_count);
    int     fill_disk(Vector<n> center, double spacing, Vector<n> velocity, double mass, Category category, uint32_t particle_count);
    void    random_fill(uint32_t particle_count);

    void    simulate(SimulationSettings settings);

    void    save_state(const std::string &filename);

private:

	SimulationSettings          _settings;              ///< The simulation settings
	SimulationConstraints<n>    _constraints;       	///< The simulation constraints
	Grid<n>                     _grid; 	                ///< The grid characteristics

	std::vector<Particle<n>>    _particles;        		///< The universe particles

	void compute_simulation();


    /// @brief Initialize the universe grid with the dimensions `size`
    /// @param size the dimensions of the grid
    void init_grid(double cell_size);

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
    void compute_cell_neighbours(int32_t id, Cell &cell);

    /// @brief Empty the grid
    void empty_grid();

    /// @brief place all the universe's particles in their coresponding cell
    void place_particles();

    /// @brief move all the universe's particles in their coresponding cell
    void update_particles_cells();

    void update_active_cells();

    /*
     * Simulation utility functions
     */

    /// @brief Update all the particles forces field using the grid
    /// @param gravitational should the gravitational force be taken into account
    /// @param lennard_jones should the lennard_jones potential force be taken into account
    void update_forces_with_grid();

    void apply_boundary_force(Particle<n>& particle, const std::vector<bool>& boundaries);

    double compute_kinetic_energy();
    void balance_kinetic_energy();

    /// @brief Reset all particles forces to zero
    void reset_forces();

};


#include "Universe.txx"

#endif //TP_PERESB_HASSANH_UNIVERSE_H
