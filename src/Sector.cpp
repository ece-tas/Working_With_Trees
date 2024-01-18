#include "Sector.h"

#include <cmath>

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
        // TODO: Calculate the distance to the Earth, and generate the sector code
        distance_from_earth = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        rounded_distance = int(distance_from_earth);
        sector_code += std::to_string(rounded_distance);
        if (x == 0)
            sector_code += "S";
        else
            sector_code += x > 0 ? "R" : "L";
        if (y == 0)
            sector_code += "S";
        else
            sector_code += y > 0 ? "U" : "D";
        if (z == 0)
            sector_code += "S";
        else
            sector_code += z > 0 ? "F" : "B";

}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary

}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator
    if (this != &other) {
        // Copy the member variables from 'other' to 'this'
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->sector_code = other.sector_code;

    }
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}
