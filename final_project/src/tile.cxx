
#include "tile.hxx"


std::ostream&
operator<<(std::ostream& os, Tile t)
{
    switch (t) {
    case Tile::pellet:
        return os << "p";
    case Tile::power_pellet:
        return os << "P";
    case Tile::wall:
        return os << "w";
    default:
        return os << "_";
    }
}