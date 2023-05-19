//
// Created by brice on 19/05/23.
//

#ifndef TP_PERESB_HASSANH_CELL_H
#define TP_PERESB_HASSANH_CELL_H


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

    std::vector<int32_t> _neighbours; ///< Indices of neighbouring cells.
    std::vector<bool> is_boundary; ///< vector of 1+2*n where n is the dimension of the grid the cell is in. The first value is true if the cell is at least a boundary cell. The second (resp. third) element after is true if the cell is a left (resp. right) boundary for the first dimension. The following couple of values hold the booleans for the next dimensions.
private:
    std::vector<uint32_t> _particles; ///< IDs of particles in the cell.
};


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

#endif //TP_PERESB_HASSANH_CELL_H
