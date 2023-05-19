//
// Created by brice on 19/05/23.
//

#ifndef TP_PERESB_HASSANH_GRID_H
#define TP_PERESB_HASSANH_GRID_H

#include "emhash_set8.h"

#include "Cell.h"

template <unsigned int n>
struct Grid {

    typedef emhash8::HashSet<uint32_t> CellHashSet; 		///< Fast Hash set used to store active cells

    std::array<int, n>   neighbour_cell_offsets;	        ///< The offset to get the neighbor of a cell for each dimension
    std::array<int32_t, n>      grid_dimensions;			///< The dimensions of the cells' grid
    double                      cell_size;					///< The physical size of each grid cell
    uint32_t                    cells_count;				///< The number of cells


    // Current grid data
    std::vector<Cell>           cells;                     ///< The array holding the cells
    CellHashSet                 active_cells;              ///< The cells currently holding at least one particle
};

#endif //TP_PERESB_HASSANH_GRID_H
