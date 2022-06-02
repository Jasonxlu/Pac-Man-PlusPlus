
#include "maze.hxx"

Maze::Maze(Dimensions dims)
            : dims_(dims)
{
    if (dims_.width < 2 || dims_.height < 2) {
        throw ge211::Client_logic_error("Board::Board: dims too small");
    }

}

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

void
Maze::bounds_check_(Position pos) const
{
    if (!good_position(pos)) {
        throw ge211::Client_logic_error("Board: position out of bounds");
    }
}


Tile
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

Tile
Maze::get_(Position pos) const
{
    if (walls_[pos]) {
        return Tile::wall;
    } else if (pellets_[pos]) {
        return Tile::pellet;
    }  else if (power_pellets_[pos]) {
        return Tile::power_pellet;
    } else {
        return Tile::path;
    }
}

void
Maze::set_(Position pos, Tile tile)
{
    switch (tile) {
    case Tile::wall:
        walls_[pos] = true;
        pellets_[pos] = false;
        power_pellets_[pos] = false;
        break;

    case Tile::pellet:
        walls_[pos] = false;
        pellets_[pos] = true;
        power_pellets_[pos] = false;
        break;

    case Tile::power_pellet:
        walls_[pos] = false;
        pellets_[pos] = false;
        power_pellets_[pos] = true;
        break;

    default:
        walls_[pos] = false;
        pellets_[pos] = false;
        power_pellets_[pos] = false;
    }
}

//returns a vector of positions corresponding to the walls in the maze.
std::vector<Maze::Position> Maze::get_maze_walls() {
    std::vector<Position> walls;
    for(int x=0; x<dims_.width; x++) {
        for(int y=0; y<dims_.height; y++) {

            if(walls_[{x,y}]) {
                walls.push_back({x,y});
            }
        }
    }
    return walls;
}



//maze positions

Maze::reference&
Maze::reference::operator=(reference const& that) noexcept
{
    *this = Tile(that);
    return *this;
}

Maze::reference&
Maze::reference::operator=(Tile tile) noexcept
{
    maze_.set_(pos_, tile);
    return *this;
}

Maze::reference::operator Tile() const noexcept
{
    return maze_.get_(pos_);
}