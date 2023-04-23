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
static constexpr std::array<int, N> power_of_3_array()
{
    std::array<int, N> arr{};
    arr[0] = 1;
    for (std::size_t i = 1; i < N; ++i) {
        arr[i] = 3 * arr[i-1];
    }
    return arr;
}

template <unsigned int n>
constexpr std::array<int, n> Universe<n>::neighbour_cell_offsets = power_of_3_array<n>();


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
        for (int i = 0; i < n; i++) {
            os << particle.get_pos()[i];
            os << " ";
        }
        for (int i = n; i < 3; i++) {
            os << "0 ";
        }
    }

    os << "\n</DataArray>\n";
    os << "</Points>\n";

    os << "<PointData Vectors=\"vector\">";

    os << "<DataArray Name=\"Velocity\" type=\"Float32\" NumberOfComponents=\"" << n << "\" format=\"ascii\">\n";
    for (Particle<n> &particle : particles) {
        for (int i = 0; i < n; i++) {
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
void Universe<n>::init_grid(std::array<int32_t, n> size) {
    // Calculate total number of cells
    uint32_t num_cells = 1;
    for (auto dim : size) {
        assert(dim > 0);
        num_cells *= dim;
    }

    // Resize cells vector
    _cells.resize(num_cells);

    for (int32_t i = 0; i < _cells.size(); i++) {
        _cells[i]._neightbours = compute_cell_neighbours(i);
    }

    // Set grid dimensions
    _grid_dimensions = size;
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

    for (int i = 0; i < neightbour_count; i++) {
        int32_t neightbour_id = id;
        int32_t neightbour_value = i;
        bool skip = false;
        for (int j = 0; j < n; j++) {
            neightbour_id = (neightbour_value % 3 - 1) * neighbour_cell_offsets[j];
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
Universe<n>::Universe(Vector<n> bottom_left, Vector<n> top_right, double cell_size)
        : _bottom_left(bottom_left), _top_right(top_right), _cell_size(cell_size)
{
    Vector<n> caract_length = top_right - bottom_left;
    std::array<int32_t, n> cells_count;
    for (uint32_t i = 0; i < n; i++) {
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
    for (uint32_t i = 0; i < particle_count; i++) {
        this->_particles.push_back(Particle<n>::random(_particles.size()));
    }
}

template <unsigned int n>
void Universe<n>::update_forces_without_grid(bool gravitational, bool lennard_jones) {

    reset_forces();

    int nb_particles = this->_particles.size();
    for (uint32_t i = 0; i<nb_particles; i++) {
        Particle<n> &p1 = this->_particles[i];
        for (uint32_t j = i + 1; j < nb_particles; j++) {
            Particle<n> &p2 = this->_particles[j];
            Particle<n>::compute_forces(p1, p2, gravitational, lennard_jones);
        }
    }
}

template <unsigned int n>
void Universe<n>::update_forces_with_grid(bool gravitational, bool lennard_jones) {

    place_particles();
    reset_forces();

    for (int32_t cell_id = 0; cell_id < _cells.size(); cell_id++) {
        std::vector<uint32_t> current_cell_particles = _cells[cell_id].get_particles();

        // Now that we have all the neighbour particles, we can update those
        for (uint32_t current_particle_id: current_cell_particles) {
            Particle<n> &current_particle = _particles[current_particle_id];
            for (int32_t neightbour_cell: _cells[cell_id]._neightbours) {
                for (uint32_t &neightbour_particle_id: _cells[neightbour_cell].get_particles()) {
                    if (current_particle_id >= neightbour_particle_id) { continue; }
                    Particle<n> &neightbour_particle = _particles[neightbour_particle_id];
                    Particle<n>::compute_forces(current_particle, neightbour_particle, gravitational, lennard_jones);
                }
            }
        }
    }
}

template<unsigned int n>
void Universe<n>::simulate(double t_end, double dt, bool gravitational, bool lennard_jones, bool use_grid, uint32_t save_each) {

    double t = 0.0;

    uint32_t nb_particles = this->_particles.size();
    std::vector<Vector<n>> F_old(nb_particles);

    // initialization of particles strengths
    if (use_grid) {
        update_forces_with_grid(gravitational, lennard_jones);
    } else {
        update_forces_without_grid(gravitational, lennard_jones);
    }

    std::stringstream ss;
    ss << "output_" << std::setfill('0') << std::setw(5) << 0 << ".vtu";
    save_state(ss.str());

    uint32_t iter = 0;
    while (t<t_end) {
        iter++;
        std::cout << "t = " << t << std::endl;
        t+=dt;

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle<n> &p = this->_particles[i];
            Vector<n> new_pos = p.get_pos() + dt * (p.get_speed() + (0.5 / p.get_mass()) * p.get_strength() * dt);
            p.set_pos(new_pos);
            F_old[i] = p.get_strength();
        }

        if (use_grid) {
            update_forces_with_grid(gravitational, lennard_jones);
        } else {
            update_forces_without_grid(gravitational, lennard_jones);
        }

        for (uint32_t i = 0; i<nb_particles; i++) {
            Particle<n> &p = this->_particles[i];
            Vector<n> new_speed = p.get_speed() + dt * (0.5 / p.get_mass()) * (p.get_strength() + F_old[i]);
            p.set_speed(new_speed);
        }

        if (save_each != 0 && iter%save_each == 0) {
            std::stringstream ss;
            ss << "output_" << std::setfill('0') << std::setw(5) << iter << ".vtu";
            save_state(ss.str());
        }
    }
}

template<unsigned int n>
int32_t Universe<n>::get_cell_id(Vector<n> position) {
    Vector<n> rel_position = position - this->_bottom_left;
    int32_t result = 0;
    for (int i = 0; i < n; i++) {
        result += floor(rel_position[i]/this->_cell_size) * neighbour_cell_offsets[i];
    }
    assert(0 <= result && result < _cells.size());
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

std::vector<uint32_t> Cell::get_particles() {
    return _particles;
}

void Cell::empty() {
    _particles.clear();
}

Cell::Cell() {
    _particles = std::vector<uint32_t>();
}
