//
// Created by brice on 13/04/23.
//

#include "Universe.h"
#include <cstdarg>

template <unsigned int n>
void Universe<n>::init_grid(CellID size) {
    // Calculate total number of cells
    uint32_t num_cells = 1;
    for (auto dim : size) {
        num_cells *= dim;
    }

    // Resize cells vector
    _cells.resize(num_cells);

    // Set grid dimensions
    _grid_dimensions = size;
}

template<unsigned int n>
std::vector<typename Universe<n>::CellID> Universe<n>::get_cell_neighbours(CellID id) {
    static int32_t neightbour_count = pow(3, n);

    std::vector<CellID> neighbours;

    for (int i = 0; i < neightbour_count; i++) {
        CellID offset;
        CellID neightbour = id;
        int32_t neightbour_value = i;
        bool skip = false;
        for (int j = 0; j < n; j++) {
            offset[j] = neightbour_value % 3;
            neightbour_value -= offset[j];
            neightbour[j] += offset[j] - 1;
            if (neightbour[j] < 0 || neightbour[j] > _grid_dimensions[j]) {
                skip = true;
                break;
            }
        }
        assert(neightbour_value == 0);
        if (skip) continue;
        neighbours.push_back(neightbour);
    }
    return neighbours;
}

template <unsigned int n>
Universe<n>::Universe(uint32_t particle_count, Vector<n> bottom_left, Vector<n> top_right, double cell_size)
        : _bottom_left(bottom_left), _top_right(top_right), _cell_size(cell_size)
{
    Vector<n> caract_length = top_right - bottom_left;
    std::vector<uint32_t> cells_count;
    for (uint32_t i = 0; i < n; i++) {
        cells_count.push_back(floor(caract_length[i]/cell_size));
    }
    init_grid();

    this->_particles.reserve(particle_count);
    static uint32_t id = 0;
    for (uint32_t particle_id = id; particle_id < id + particle_count; particle_id++) {
        this->_particles.push_back(Particle<n>::random(particle_id));
    }
    id += particle_count;
}

template <unsigned int n>
void Universe<n>::update_strengths() {
    int nb_particles = this->_particles.size();
    Vector<n> F_i;
    Vector<n> R_ij;
    double r_ij;
    double r_ij_sq;
    double r_cut = 2.5;

    // parameters for Lennard Jones' potential
    double eps = 1.0;
    double sigma = 1.0;
    double sigma_exp_six = sigma * sigma * sigma * sigma * sigma * sigma;

    for (uint32_t i = 0; i<nb_particles; i++) {
        F_i = Vector<n>();
        for (uint32_t j = 0; j < nb_particles; j++) {
            if (j != i) {
                R_ij = this->_particles[j].get_pos() - this->_particles[i].get_pos();
                r_ij = R_ij.length();
                r_ij_sq = r_ij * r_ij;

                // gravitational strength
                F_i += (this->_particles[i].get_mass() * this->_particles[j].get_mass() / r_ij_sq) * R_ij;

                if (j != 1 && r_ij <= r_cut) {
                    double r_ij_exp_six = r_ij_sq * r_ij_sq * r_ij_sq;
                    double sigma_ov_r_ij = sigma_exp_six/r_ij_exp_six;
                    // interactions (Lennard-Jones)
                    F_i += 24.0 * eps * 1/r_ij_sq * (sigma_ov_r_ij) * (1.0 - 2.0 * sigma_ov_r_ij) * R_ij;
                }
            }
        }
        this->_particles[i].set_strength(F_i);
    }
}

/**
 * Simulation of particles using the Stormer Verlet algorithm
 * @param t_end : maximum time of the simulation
 * @param dt : time step
 */
template <unsigned int n>
void Universe<n>::simulate(double t_end, double dt) {

    double t = 0.0;

    uint32_t nb_particles = this->_particles.size();

    std::vector<Vector<n>> F_old(nb_particles);

    // initialization of particles strengths
    update_strengths();

    while (t<t_end) {
        t+=dt;

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle<n> &p = this->_particles[i];
            Vector<n> new_pos = p.get_pos() + dt * (p.get_speed() + (0.5 / p.get_mass()) * p.get_speed() * dt);
            p.set_pos(new_pos);
            F_old[i] = p.get_strength();
        }

        update_strengths();

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle p = this->_particles[i];
            Vector<n> new_speed = p.get_speed() + dt * (0.5 / p.get_mass()) * (p.get_strength() + F_old[i]);
            p.set_speed(new_speed);
        }
    }
}


template<unsigned n>
template<typename... Args>
typename Universe<n>::CellID Universe<n>::get_cell_id(Args... args) {
    static_assert(sizeof...(Args) == n, "Wrong number of arguments provided");
    static_assert((std::is_same_v<Args, uint32_t> && ...), "All arguments must be of type uint32_t.");

    size_t cell_index = 0;
    uint32_t fact = n;
    for (int i = 0; i < n; i++) {
        cell_index += ((args * fact) + ...);
        fact *= n;
    }
    return this->_cells[cell_index];
}

template<unsigned int n>
typename Universe<n>::CellID Universe<n>::get_cell_id(Vector<n> position) {
    Vector<n> rel_position = position - this->_bottom_left;
    std::vector<uint32_t> result;
    for (int i = 0; i < n; i++) {
        result.push_back(floor(rel_position[i]/this->_cell_size));
    }
    return result;
}

template<unsigned int n>
void Universe<n>::place_particles() {

}

template<unsigned int n>
uint32_t Universe<n>::get_cell_linear_id(Universe::CellID id) {
    uint32_t cell_linear_id;
    uint32_t fact = n;
    for (int i = 0; i < n; i++) {
        cell_linear_id += fact * id[i];
        fact *= n;
    }
    return cell_linear_id;
}

template<unsigned int n>
Cell Universe<n>::get_cell_with_id(Universe::CellID id) {
    return _cells[get_cell_linear_id(id)];
}