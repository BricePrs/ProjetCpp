//
// Created by brice on 13/04/23.
//

#include "Universe.h"
#include <fstream>
#include <sstream>
#include <iomanip>

/*
 * Setting static values for Universe<n>
 */

template <std::size_t N>
static constexpr std::array<int, N> compute_offsets_array(std::array<int, N> &dimensions)
{
    std::array<int, N> arr{};
    arr[0] = 1;
    for (std::size_t i = 1; i < N; ++i) {
        arr[i] = dimensions[i-1] * arr[i-1];
    }
    return arr;
}

void write_header(std::ostream& os) {
    os << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\n"
          "<UnstructuredGrid>\n";
}

void write_footer(std::ostream& os) {
    os << "</UnstructuredGrid>\n"
          "</VTKFile>\n";
}
void write_cells(std::ostream& os) {
    os << "<Cells>\n"
          "<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n"
          "</DataArray>\n"
          "<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n"
          "</DataArray>\n"
          "<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n"
          "</DataArray>\n"
          "</Cells>\n";
}

template <unsigned int n>
void write_particles(std::ostream& os, std::vector<Particle<n>> &particles) {
    static_assert(n <= 3, "Cannot write for n greater than 3");
    os << "<Points>\n";
    os << "<DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    for (Particle<n> &particle : particles) {
        for (int i = 0; i < n; ++i) {
            os << particle.get_pos()[i];
            os << " ";
        }
        for (int i = n; i < 3; ++i) {
            os << "0 ";
        }
    }

    os << "\n</DataArray>\n";
    os << "</Points>\n";

    os << "<PointData Vectors=\"vector\">";

    os << "<DataArray Name=\"Velocity\" type=\"Float32\" NumberOfComponents=\"" << n << "\" format=\"ascii\">\n";
    for (Particle<n> &particle : particles) {
        for (int i = 0; i < n; ++i) {
            os << particle.get_speed()[i];
            os << " ";
        }
    }
    os << "\n</DataArray>\n";

    os << "<DataArray Name=\"Masse\" type=\"Float32\" format=\"ascii\">\n";
    for (Particle<n> &particle : particles) {
        os << particle.get_mass();
        os << " ";
    }
    os << "\n</DataArray>\n";
    os << "</PointData>\n";

}

template<unsigned int n>
int Universe<n>::add_packed_particles(Vector<n> bottom_left, Vector<n> top_right, Vector<n> velocity, double mass, Category category, Vector<n> particle_count) {
    Vector<n> spacing = (top_right - bottom_left) / (particle_count - Vector<n>(1.));
    int particle_total = 1.;
    for (int dim = 0; dim < n; ++dim) {
        particle_total *= particle_count[dim];
    }

    Vector<n> index = Vector<n>(0.);
    index[0] = -1;
    for (int i = 0; i < particle_total; ++i) {
        index[0] += 1;
        for (int dim = 0; dim < n; ++dim) {
            if (index[dim] >= particle_count[dim]) {
                index[dim] = 0;
                index[dim + 1]++;
            }
        }
        auto a = index * spacing;
        add(bottom_left + index * spacing, velocity, mass, category);

    }
    return particle_total;
}

template <unsigned int n>
void Universe<n>::init_grid(std::array<int32_t, n> size) {
    // Calculate total number of cells
    _cells_count = 1;
    for (auto dim : size) {
        assert(dim > 0);
        _cells_count *= dim;
    }

    // Resize cells vector
    _cells.resize(_cells_count);

    // Set grid dimensions
    _grid_dimensions = size;
    _neighbour_cell_offsets = compute_offsets_array(_grid_dimensions);

    for (int32_t i = 0; i < _cells_count; ++i) {
        _cells[i]._neightbours = compute_cell_neighbours(i);
    }


}

template <unsigned int n>
void Universe<n>::save_state(const std::string &filename) {
    static_assert(n <= 3, "Cannot save state for dimensions greater than 3");
    std::ofstream outfile;
    outfile.open(filename);

    write_header(outfile);

    outfile << "<Piece NumberOfPoints=\"" << _particles.size() << "\" NumberOfCells=\"0\">\n";

    write_particles<n>(outfile, _particles);
    write_cells(outfile);

    outfile << "</Piece>\n";

    write_footer(outfile);

    outfile.close();
}



template<unsigned int n>
std::vector<int32_t> Universe<n>::compute_cell_neighbours(int32_t id) {
    static int32_t neightbour_count = pow(3, n);

    std::vector<int32_t> neighbours;

    for (int i = 0; i < neightbour_count; ++i) {
        int32_t neightbour_id = id;
        int32_t neightbour_value = i;
        bool skip = false;
        for (int j = 0; j < n; ++j) {
            neightbour_id += (neightbour_value % 3 - 1) * _neighbour_cell_offsets[j];
            neightbour_value /= 3;
            if (neightbour_id < 0 || neightbour_id >= _cells.size()) {
                skip = true;
                break;
            }
        }
        if (skip) continue;
        assert(neightbour_value == 0);
        neighbours.push_back(neightbour_id);
    }
    return neighbours;
}


template <unsigned int n>
Universe<n>::Universe(Vector<n> bottom_left, Vector<n> top_right, double cell_size, BoundaryBehaviour boundary_behaviour)
        : _bottom_left(bottom_left), _top_right(top_right), _cell_size(cell_size), _boundary_behaviour(boundary_behaviour), _center((bottom_left + top_right)/2.), _width(_center-bottom_left)
{
    Vector<n> caract_length = top_right - bottom_left;
    std::array<int32_t, n> cells_count;
    for (uint32_t i = 0; i < n; ++i) {
        cells_count[i] = floor(caract_length[i]/cell_size);
    }
    init_grid(cells_count);
}

template<unsigned int n>
void Universe<n>::add(Vector<n> position, Vector<n> velocity, double mass, Category category) {
    static uint32_t max_id;
    _particles.push_back(Particle<n>(max_id, position, velocity, mass, category));
    max_id++;
}

template<unsigned int n>
void Universe<n>::random_fill(uint32_t particle_count) {
    for (uint32_t i = 0; i < particle_count; ++i) {
        this->_particles.push_back(Particle<n>::random(_particles.size()));
    }
}

template <unsigned int n>
void Universe<n>::update_forces_without_grid(bool gravitational, bool lennard_jones) {

    reset_forces();

    int nb_particles = this->_particles.size();
    for (uint32_t i = 0; i<nb_particles; ++i) {
        Particle<n> &p1 = this->_particles[i];
        for (uint32_t j = i + 1; j < nb_particles; ++j) {
            Particle<n> &p2 = this->_particles[j];
            Particle<n>::compute_forces(p1, p2, gravitational, lennard_jones);
        }
    }
}

template <unsigned int n>
void update_forces_with_grid_range(std::vector<Particle<n>> &particles, std::vector<Cell> &cells, bool gravitational, bool lennard_jones, int32_t grid_lb, int32_t grid_ub) {
    uint32_t closest = 0;
    for (int32_t cell_id = grid_lb; cell_id < grid_ub; ++cell_id) {
        std::vector<uint32_t> &current_cell_particles = cells[cell_id].get_particles();

        // Now that we have all the neighbour particles, we can update those
        for (uint32_t current_particle_id: current_cell_particles) {
            uint32_t closest_local = 0;
            Particle<n> &current_particle = particles[current_particle_id];
            for (int32_t neightbour_cell: cells[cell_id]._neightbours) {
                for (uint32_t neightbour_particle_id: cells[neightbour_cell].get_particles()) {
                    if (current_particle_id >= neightbour_particle_id) { continue; }
                    Particle<n> &neightbour_particle = particles[neightbour_particle_id];
                    if (lennard_jones || gravitational) {
                        Particle<n>::compute_forces(current_particle, neightbour_particle, gravitational, lennard_jones);
                    }
                }
            }
        }
    }
}

template <unsigned int n>
void Universe<n>::update_forces_with_grid(bool gravitational, bool lennard_jones, uint32_t threads) {
    if (threads <= 1) {
        update_forces_with_grid_range(gravitational, lennard_jones, 0, _cells_count);
    } else {
        struct ThreadArgs {
            bool gravitational;
            bool lennard_jones;
            int32_t lb;
            int32_t ub;
        };
        std::unique_ptr<pthread_t> thread_array[threads];

        for (int i = 0; i < threads; ++i) {
            ThreadArgs args = { gravitational, lennard_jones, i * _cells_count / threads, (i+1) * _cells_count / threads };
            pthread_create(thread_array[i], nullptr, update_forces_with_grid_range, &args);
        }

    }
    uint32_t closest = 0;
    for (int32_t cell_id = 0; cell_id < _cells_count; ++cell_id) {
        std::vector<uint32_t> &current_cell_particles = _cells[cell_id].get_particles();

        // Now that we have all the neighbour particles, we can update those
        for (uint32_t current_particle_id: current_cell_particles) {
            uint32_t closest_local = 0;
            Particle<n> &current_particle = _particles[current_particle_id];
            for (int32_t neightbour_cell: _cells[cell_id]._neightbours) {
                for (uint32_t neightbour_particle_id: _cells[neightbour_cell].get_particles()) {
                    if (current_particle_id >= neightbour_particle_id) { continue; }
                    Particle<n> &neightbour_particle = _particles[neightbour_particle_id];
                    if (lennard_jones || gravitational) {
                        Particle<n>::compute_forces(current_particle, neightbour_particle, gravitational, lennard_jones);
                    }
                }
            }
        }
    }
}

template<unsigned int n>
void Universe<n>::simulate(double t_end, double dt, bool gravitational, bool lennard_jones, bool use_grid, uint32_t save_each, uint32_t threads) {

    auto starting_time = std::chrono::steady_clock::now();

    double t = 0.0;

    uint32_t nb_particles = this->_particles.size();
    std::vector<Vector<n>> F_old(nb_particles);
    auto max_iter = static_cast<int32_t>(t_end/dt);
    auto max_digits_to_save = static_cast<int32_t>(ceil(log10( max_iter/save_each))+1);

    reset_forces();
    // initialization of particles strengths
    if (use_grid) {
        place_particles();
        update_forces_with_grid(gravitational, lennard_jones, threads);
    } else {
        update_forces_without_grid(gravitational, lennard_jones, threads);
    }

    std::stringstream ss;
    ss << "output_" << std::setfill('0') << std::setw(max_digits_to_save) << 0 << ".vtu";
    save_state(ss.str());

    uint32_t iter_until_next_display = 0;
    uint32_t iter = 0;
    while (t<t_end) {
        iter++;
        if (iter_until_next_display == 0) {
            iter_until_next_display = max_iter/1000;
            std::stringstream ss;
            std::chrono::duration<double> duration = std::chrono::steady_clock::now() - starting_time;
            ss << std::setprecision(3) << std::fixed << "Computing : " << int(floor(iter*1000./max_iter)/10.) << "% done : time = " << t << " : ETA = " << duration.count() * (max_iter - iter) / iter << "s";
            std::cout << ss.str() << std::endl;
        } else {
            iter_until_next_display--;
        }
        t+=dt;

        for (uint32_t i = 0; i<nb_particles; ++i) {
            Particle<n> &p = this->_particles[i];
            Vector new_pos = p.get_pos() + dt * (p.get_speed() + (0.5 / p.get_mass()) * p.get_strength() * dt);
            p.set_pos(new_pos);
            F_old[i] = p.get_strength();
            p.set_force(Vector<n>::zero()); // Resetting all forces to zero
        }

        if (use_grid) {
            update_particles_cells();
            update_forces_with_grid(gravitational, lennard_jones, threads);
        } else {
            update_forces_without_grid(gravitational, lennard_jones, threads);
        }

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle<n> &p = this->_particles[i];
            Vector<n> new_speed = p.get_speed() + dt * (0.5 / p.get_mass()) * (p.get_strength() + F_old[i]);
            p.set_speed(new_speed);
        }

        if (save_each != 0 && iter%save_each == 0) {
            std::stringstream ss;
            ss << "output_" << std::setfill('0') << std::setw(max_digits_to_save) << iter << ".vtu";
            save_state(ss.str());
        }
    }
}

template<unsigned int n>
inline int32_t Universe<n>::get_cell_id(Vector<n> position) {
    Vector<n> rel_position = (position - _bottom_left) / this->_cell_size;
    int32_t result = 0;
    for (int i = 0; i < n; ++i) {
        result += floor(rel_position[i]) * _neighbour_cell_offsets[i];
    }
    return result;
}


template<unsigned int n>
void Universe<n>::place_particles() {
    empty_grid();
    for (Particle particle: _particles) {
        _cells[get_cell_id(particle.get_pos())].place(particle.get_id());
    }
}

template<unsigned int n>
void Universe<n>::update_particles_cells() {
    for (int32_t cell_id = 0; cell_id < _cells_count; cell_id++) {
        Cell &cell = _cells[cell_id];
        auto &particle_set = cell.get_particles();
        for (auto it = particle_set.begin(); it != particle_set.end();) {
            int32_t new_cell_id = get_cell_id(_particles[*it].get_pos());
            if (0 > new_cell_id && new_cell_id >= _cells_count) {
                switch (_boundary_behaviour) {
                    case Reflexive: {
                        Vector rel_pos = _particles[*it].get_pos() - _center;
                        Vector<n> p_velocity = _particles[*it].get_speed();
                        for (int i = 0; i < n; ++i) {
                            rel_pos[i] = fmax((fabs(rel_pos[i]) - _width[i]), 0.);
                            if (rel_pos[i] > 0.) {
                                p_velocity[i] = -p_velocity[i];
                            }
                        }
                        _particles[*it].set_speed(p_velocity);
                        new_cell_id = get_cell_id(_particles[*it].get_pos() - rel_pos);
                    }
                        break;
                    case Absorption: {
                        _particles.erase(_particles.begin() + *it);
                        it = particle_set.erase(it);
                        continue;
                    }
                    case Periodic: {
                        _particles[*it].set_pos(
                                (_particles[*it].get_pos() - _bottom_left) % (_top_right - _bottom_left)+_bottom_left);
                        new_cell_id = get_cell_id(_particles[*it].get_pos());
                    }
                        break;
                }
            }
            if (new_cell_id != cell_id) {
                _cells[new_cell_id].place(*it);
                it = particle_set.erase(it);

            } else {
                ++it;
            }

        }
    }
}

template<unsigned int n>
void Universe<n>::empty_grid() {
    for (Cell &cell: _cells) {
        cell.empty();
    }
}

template<unsigned int n>
void Universe<n>::reset_forces() {
    for (Particle<n> &p: _particles) {
        p.set_force(Vector<n>::zero());
    }
}

template<unsigned int n>
Cell Universe<n>::get_cell_with_id(int32_t id) {
    return _cells[id];
}

void Cell::place(uint32_t id) {
    _particles.push_back(id);
}

std::vector<uint32_t> &Cell::get_particles() {
    return _particles;
}

void Cell::empty() {
    _particles.erase(_particles.begin(), _particles.end());
}

Cell::Cell() {
    _particles = std::vector<uint32_t>();
}

void Cell::lock() {
    pthread_mutex_lock(&this->mutex)
}

void Cell::unlock() {
    pthread_mutex_unlock(&this->mutex)
}
