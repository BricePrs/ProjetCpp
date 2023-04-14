//
// Created by helen on 14/04/23.
//

#ifndef TP_PERESB_HASSANH_CELL_H
#define TP_PERESB_HASSANH_CELL_H

#include <cstdint>

class Grid {
public:
    Grid(uint32_t N, uint32_t L_d);
private:
    uint32_t nc_d;
    uint32_t L_d;
    uint32_t N;
};

#endif //TP_PERESB_HASSANH_CELL_H
