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
        for (uint32_t i = 0; i < n; ++i) {
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
        for (uint32_t i = 0; i < n; ++i) {
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
int Universe<n>::add_packed_particles(Vector<n> bottom_left, Vector<n> top_right, Vector<n> velocity, double mass, Category category, Vector<n> particle_count) {
    Vector<n> spacing = (top_right - bottom_left) / (particle_count - Vector<n>(1.));
    int particle_total = 1.;
    for (uint32_t  dim = 0; dim < n; ++dim) {
        particle_total *= particle_count[dim];
    }

    Vector<n> index = Vector<n>(0.);
    index[0] = -1;
    for (int i = 0; i < particle_total; ++i) {
        index[0] += 1;
        for (uint32_t  dim = 0; dim < n; ++dim) {
            if (index[dim] >= particle_count[dim]) {
                index[dim] = 0;
                index[dim + 1]++;
            }
        }
        add(bottom_left + index * spacing, velocity, mass, category);
    }
    return particle_total;
}

template<unsigned int n>
int Universe<n>::fill_sphere(Vector<n> bottom_left, Vector<n> top_right, Vector<n> velocity, double mass, Category category, Vector<n> particle_count) {
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
void Universe<n>::init_grid(double cell_size) {

    _grid.cell_size = cell_size;

    Vector<n> caract_length = _constraints.width*2.;
    std::array<int32_t, n> grid_dimensions;
    for (uint32_t i = 0; i < n; ++i) {
        grid_dimensions[i] = floor(caract_length[i] / cell_size);
    }

    // Compute total number of cells
    _grid.cells_count = 1;
    for (auto dim : grid_dimensions) {
        assert(dim > 0);
        _grid.cells_count *= dim;
    }

    _grid.cells = std::vector<Cell>(_grid.cells_count);
    _grid.active_cells.reserve(_grid.cells_count, false);

    // Set grid dimensions
    _grid.grid_dimensions = grid_dimensions;
    _grid.neighbour_cell_offsets = compute_offsets_array(_grid.grid_dimensions);

    for (uint32_t i = 0; i < _grid.cells_count; ++i) {
        compute_cell_neighbours(i, _grid.cells[i]);
    }
}



template<unsigned int n>
void Universe<n>::compute_cell_neighbours(int32_t id, Cell &cell) {

    // Computing the cell coordinates in coords
    std::array<int32_t, n> coords;
    int32_t id_coords = id;
    for (uint32_t i = 0; i < n; ++i) {
        coords[i] = id_coords % _grid.grid_dimensions[i];
        id_coords /= _grid.grid_dimensions[i];
    }

    // A cell has 3^n neighbours (including the cell)
    static int32_t neighbour_count = pow(3, n);


    std::vector<int32_t> neighbours;
    for (int i = 0; i < neighbour_count; ++i) {

        int32_t neighbour_id = 0;
        std::array<int32_t, n> neighbour_coords(coords);
        bool skip = false;
        int32_t neighbour_offset_value = i;

        for (uint32_t j = 0; j < n; ++j) {
            neighbour_coords[j] += (neighbour_offset_value % 3) - 1;
            neighbour_offset_value /= 3;
            if (_settings.boundary_behaviour == Periodic) {
                neighbour_coords[j] %= _grid.grid_dimensions[j];
                if (neighbour_coords[j] < 0) {
                    neighbour_coords[j] += _grid.grid_dimensions[j];
                }
            } else if (neighbour_coords[j] < 0 || neighbour_coords[j] >= _grid.grid_dimensions[j]) {
                skip = true;
                break;
            }

            neighbour_id += neighbour_coords[j] * _grid.neighbour_cell_offsets[j];
        }

        if (skip) {
            continue;
        }

        neighbours.push_back(neighbour_id);
    }

    // First bool is set to true if the cell is not a boundary
    // Next two bool are set to true if the left (resp. right) is a boundary of the first dimension
    // repeat two bool for each dimension
    bool is_boundary = false;
    auto boundaries = std::vector<bool>(1 + 2*n);
    for (uint32_t j = 0; j < 2*n; ++j) {
        if (coords[j] == 0) {
            boundaries[1+2*j] = true;
            is_boundary = true;
        }
        if (coords[j] == _grid.grid_dimensions[1] - 1) {
            boundaries[1+2*j+1] = true;
            is_boundary = true;
        }
    }

    // Setting the first elt of the cell boundaries to true if there is at least one boundary, else to false
    boundaries[0] = is_boundary;

    // Setting the cells' neighbours
    cell._neighbours = neighbours;
    cell.is_boundary = boundaries;
}


template <unsigned int n>
Universe<n>::Universe(SimulationConstraints<n> constraints, double cell_size)
        : _constraints(constraints)
{
    init_grid(cell_size);
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
        _particles.push_back(Particle<n>::random(_particles.size()));
    }
}

template <unsigned int n>
void Universe<n>::apply_boundary_force(Particle<n>& particle, const std::vector<bool>& boundaries) {
    for (uint32_t i = 0; i < n; ++i) {
        Vector dir = Vector<n>::unit(i);
        if (boundaries[1+2*i]) {
            particle.apply_force(-dir * Particle<n>::compute_lennard_jones_intensity(
                    pow(particle.get_pos()[i] - _constraints.bottom_left[i], 2.)));
        }
        if (boundaries[1+2*i+1]) {
            particle.apply_force(dir * Particle<n>::compute_lennard_jones_intensity(
                    pow(particle.get_pos()[i] - _constraints.top_right[i], 2.)));
        }
    }
}

template<unsigned int n>
void Universe<n>::balance_kinetic_energy() {
    double current_kinetic_energy = compute_kinetic_energy();
    double beta = sqrt(_settings.goal_kinetic_energy / current_kinetic_energy);
    for (Particle particle: _particles) {
        particle.set_speed(particle.get_speed()*beta);
    }
}

template<unsigned int n>
double Universe<n>::compute_kinetic_energy() {
    double energy = 0;
    for (Particle particle: _particles) {
        energy += particle.kinetic_energy();
    }
    return energy;
}

template <unsigned int n>
void Universe<n>::update_forces_with_grid() {

    for (int32_t cell_id : _grid.active_cells) {
        Cell &current_cell = _grid.cells[cell_id];
        std::vector<uint32_t> &current_cell_particles = current_cell.get_particles();
        // Now that we have all the neighbour particles, we can update those
        for (uint32_t current_particle_id: current_cell_particles) {
            Particle<n> &current_particle = _particles[current_particle_id];
            for (int32_t neighbour_cell: _grid.cells[cell_id]._neighbours) {
                // If the neighbour cells is not active we don't check it
                if (!_grid.active_cells.contains(neighbour_cell)) { continue; }
                for (uint32_t neighbour_particle_id: _grid.cells[neighbour_cell].get_particles()) {
                    if (current_particle_id >= neighbour_particle_id) { continue; }
                    Particle<n> &neighbour_particle = _particles[neighbour_particle_id];
                    if (_settings.lennard_jones_interaction || _settings.gravitational_interaction) {
                        Particle<n>::compute_forces(
                                current_particle,
                                neighbour_particle,
                                _settings.lennard_jones_interaction,
                                _settings.gravitational_interaction
                        );
                    }
                }
            }

            if (_settings.external_gravity) {
                current_particle.apply_gravity();
            }

        }

        // Adding the eventual forces exercised on the current particle by the boundaries
        if (_settings.boundary_behaviour == ReflexivePotential && current_cell.is_boundary[0]) {
            std::vector<bool> &boundaries = current_cell.is_boundary;
            for (uint32_t current_particle_id: current_cell_particles) {
                apply_boundary_force(_particles[current_particle_id], boundaries);
            }
        }
    }
}

template<unsigned int n>
void Universe<n>::simulate(SimulationSettings settings) {

    // Initializing simulation
    _settings = settings;

    // Actual simulation
    compute_simulation();

}

template<unsigned int n>
void Universe<n>::compute_simulation() {

    auto starting_time = std::chrono::steady_clock::now();

    double t = 0.0;

    uint32_t nb_particles = this->_particles.size();
    std::vector<Vector<n>> F_old(nb_particles);
    auto max_iter           = static_cast<int32_t>(_settings.physics_time_total/_settings.physics_time_step);
    auto max_digits_to_save = static_cast<int32_t>(ceil(log10(max_iter/_settings.iter_count_until_save))+1);

    reset_forces();
    // initialization of particles strengths
    place_particles();
    update_forces_with_grid();

    std::stringstream ss;
    ss << "output_" << std::setfill('0') << std::setw(max_digits_to_save) << 0 << ".vtu";
    save_state(ss.str());

    uint32_t iter_until_next_display = 0;
    uint32_t iter = 0;
    while (t < _settings.physics_time_total) {
        iter++;

        // Displaying real time info about pending simulation
        if (iter_until_next_display == 0) {
            iter_until_next_display = max_iter/1000;
            std::stringstream ss;
            std::chrono::duration<double> duration = std::chrono::steady_clock::now() - starting_time;
            ss << std::setprecision(3) << std::fixed << "Computing : " << int(floor(iter*1000./max_iter)/10.) << "% done : time = " << t << " : ETA = " << duration.count() * (max_iter - iter) / iter << "s";
            std::cout << ss.str() << std::endl;
        } else {
            iter_until_next_display--;
        }
        t+=_settings.physics_time_step;

        for (uint32_t cell_id : _grid.active_cells) {
            Cell &cell = _grid.cells[cell_id];
            for (uint32_t particle_id: cell.get_particles()) {
                Particle<n> &p = _particles[particle_id];
                Vector new_pos = p.get_pos() + _settings.physics_time_step * (p.get_speed() + (0.5 / p.get_mass()) * p.get_strength() * _settings.physics_time_step);
                p.set_pos(new_pos);
                F_old[p.get_id()] = p.get_strength();
                p.set_force(Vector<n>::zero()); // Resetting all forces to zero
            }
        }

        update_particles_cells();
        update_forces_with_grid();

        for (uint32_t cell_id : _grid.active_cells) {
            Cell &cell = _grid.cells[cell_id];
            for (uint32_t particle_id: cell.get_particles()) {
                Particle<n> &p = _particles[particle_id];
                Vector<n> new_speed = p.get_speed() + _settings.physics_time_step * (0.5 / p.get_mass()) * (p.get_strength() + F_old[p.get_id()]);
                p.set_speed(new_speed);
            }
        }

        if (_settings.iter_count_until_save != 0 && iter%_settings.iter_count_until_save == 0) {
            std::stringstream ss;
            ss << "output_" << std::setfill('0') << std::setw(max_digits_to_save) << iter << ".vtu";
            save_state(ss.str());
        }
    }
}

template<unsigned int n>
inline int32_t Universe<n>::get_cell_id(Vector<n> position) {
    Vector<n> rel_position = (position - _constraints.bottom_left) / _grid.cell_size;
    int32_t result = 0;
    for (uint32_t i = 0; i < n; ++i) {
        int32_t coord = floor(rel_position[i]);
        if (coord < 0 || _grid.grid_dimensions[i] < coord) {
            return -1;
        } else if (coord == _grid.grid_dimensions[i]) {
            if (position[i] <= _constraints.top_right[i]){
                coord -= 1;
            } else {
                return -1;
            }
        }
        result += coord * _grid.neighbour_cell_offsets[i];
    }
    return result;
}


template<unsigned int n>
void Universe<n>::place_particles() {
    empty_grid();
    for (Particle particle: _particles) {
        int32_t id = get_cell_id(particle.get_pos());
        assert(id >= 0);
        _grid.cells[id].place(particle.get_id());
    }
}

template<unsigned int n>
void Universe<n>::update_particles_cells() {

    for (uint32_t cell_id: _grid.active_cells) {

        Cell &cell = _grid.cells[cell_id];
        auto &particle_set = cell.get_particles();

        for (auto it = particle_set.begin(); it != particle_set.end();) {

            int32_t new_cell_id = get_cell_id(_particles[*it].get_pos());
            if (0 > new_cell_id || new_cell_id >= (int) _grid.cells_count) {
                switch (_settings.boundary_behaviour) {
                    case Reflexive: {
                        while (0 > new_cell_id || new_cell_id >= (int) _grid.cells_count) {
                            Vector rel_pos = _particles[*it].get_pos() - _constraints.center;
                            Vector<n> offset;
                            Vector<n> p_velocity = _particles[*it].get_speed();
                            for (uint32_t i = 0; i < n; ++i) {
                                offset[i] = fabs(rel_pos[i]) - _constraints.width[i];
                                if (offset[i] >= 0.) {
                                    p_velocity[i] = -p_velocity[i];
                                } else {
                                    offset[i] = 0.;
                                }
                                if (rel_pos[i] < 0.) {
                                    offset[i] *= -1.;
                                }
                            }
                            _particles[*it].set_speed(p_velocity);
                            _particles[*it].set_pos(_particles[*it].get_pos() - 2.*offset);
                            new_cell_id = get_cell_id(_particles[*it].get_pos());
                        }
                    }
                        break;
                    case Absorption: {
                        it = particle_set.erase(it);
                        continue;
                    }
                    case Periodic: {
                            _particles[*it].set_pos(
                                    (_particles[*it].get_pos() - _constraints.bottom_left) %
                                    (_constraints.top_right- _constraints.bottom_left) +
                                    _constraints.bottom_left
                            );
                            new_cell_id = get_cell_id(_particles[*it].get_pos());
                        }
                        break;
                    default:
                        break;
                }
            }
            if (new_cell_id != (int) cell_id) {
                _grid.cells[new_cell_id].place(*it);
                it = particle_set.erase(it);
            } else {
                ++it;
            }
        }
    }

    update_active_cells();

}

template<unsigned int n>
void Universe<n>::update_active_cells() {
    for (uint32_t cell_id = 0; cell_id < _grid.cells.size(); ++cell_id) {
        if (_grid.cells[cell_id].get_particles().empty()) {
            _grid.active_cells.erase(cell_id);
        } else {
            _grid.active_cells.insert(cell_id);
        }
    }
}

template<unsigned int n>
void Universe<n>::empty_grid() {
    for (Cell &cell: _grid.cells) {
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
    return _grid.cells[id];
}

