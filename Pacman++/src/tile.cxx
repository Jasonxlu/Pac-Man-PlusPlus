
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
    case Tile::spawn_point:
        return os << "s";
    default:
        return os << "_";
    }
}