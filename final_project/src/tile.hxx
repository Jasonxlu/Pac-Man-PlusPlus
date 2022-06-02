

#pragma once

#include <iostream>

// A wall or pellet or power_pellet or a path
enum class Tile
{
    pellet,
    power_pellet,
    wall,
    path
};

// Prints a tile in a manner suitable for debugging.
std::ostream& operator<<(std::ostream&, Tile);
