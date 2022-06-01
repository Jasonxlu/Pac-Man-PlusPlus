
#include "maze.hxx"

Maze::Maze(Dimensions dims)
            : dims_(dims)
{}

Maze::Dimensions
Maze::dimensions() const
{
    return dims_;
}

bool
Maze::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}

std::vector<Maze::Rectangle>
Maze::get_walls()
{
    return walls_;
}

bool
Maze::get_(Position pos) const
{
    for(Maze::Rectangle w : walls_) {
        if (w.x == pos.x && w.y == pos.y) { //there is a wall here
            return true;
        }
    }

    return false;
}

void
Maze::bounds_check_(Position pos) const
{
    if (!good_position(pos)) {
        throw ge211::Client_logic_error("Board: position out of bounds");
    }
}


bool
Maze::operator[](Position pos) const
{
    bounds_check_(pos);
    return get_(pos);
}

std::vector<Maze::Dimensions> const&
Maze::all_directions_randomized()
{
    std::vector<Dimensions> result;

    result.push_back({0,1}); //down
    result.push_back({0,-1}); //up
    result.push_back({1,0}); //left
    result.push_back({-1,0}); //right

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(result), std::end(result), rng);
    return result;
}