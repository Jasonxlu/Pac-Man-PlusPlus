
#include "maze.hxx"

Maze::Maze(Dimensions dims)
            : dims_(dims),
            num_pellets_(0)
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

Maze::reference
Maze::operator[](Position pos)
{
    bounds_check_(pos);
    return reference(*this, pos);
}

Maze::reference::reference(Maze& maze, Position pos) noexcept
        : maze_(maze),
          pos_(pos)
{ }


std::vector<Maze::Dimensions>
Maze::all_directions()
{
    std::vector<Dimensions> result;

    result.push_back({0,1}); //down
    result.push_back({0,-1}); //up
    result.push_back({1,0}); //left
    result.push_back({-1,0}); //right

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
    } else if (spawn_points_[pos]) {
        return Tile::spawn_point;
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
        spawn_points_[pos] = false;
        break;

    case Tile::pellet:
        walls_[pos] = false;
        pellets_[pos] = true;
        power_pellets_[pos] = false;
        spawn_points_[pos] = false;
        break;

    case Tile::power_pellet:
        walls_[pos] = false;
        pellets_[pos] = false;
        power_pellets_[pos] = true;
        spawn_points_[pos] = false;
        break;

    case Tile::spawn_point:
        walls_[pos] = false;
        pellets_[pos] = false;
        power_pellets_[pos] = false;
        spawn_points_[pos] = true;
        break;

    default:
        walls_[pos] = false;
        pellets_[pos] = false;
        power_pellets_[pos] = false;
        spawn_points_[pos] = false;
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

void
Maze::destroy_pellet(Position p)
{
    Tile before = get_(p);
    set_(p,Tile::path);

    //check before = pellet and after = just a path
    //if so, decrement num_pellets.
    if(((before == Tile::pellet) && (get_(p) == Tile::path)) ||
            ((before == Tile::power_pellet) && (get_(p) == Tile::path))) {
        num_pellets_--;
    }

}


//returns a vector of positions corresponding to the pellets in the maze.
std::vector<Maze::Position> Maze::get_maze_pellets() {
    std::vector<Position> pellets;
    for(int x=0; x<dims_.width; x++) {
        for(int y=0; y<dims_.height; y++) {

            if(pellets_[{x,y}]) {
                pellets.push_back({x,y});
            }
        }
    }
    return pellets;
}


void
Maze::set_pellets() {
    for(int i=0; i<dims_.width; i++) {
        for(int j=0; j<dims_.height; j++) {
            if(get_({i,j}) == Tile::path) {
                set_({i, j}, Tile::pellet);
                num_pellets_ += 1;
            } else if(get_({i,j}) == Tile::power_pellet) {
                num_pellets_ += 1;
            }//also add to counter if it's a power pellet
        }
    }
}

bool
Maze::all_pellets_eaten()
{
    return (num_pellets_ == 0);
}

bool
Maze::operator==(Maze b)
{
    return (walls_ == b.walls_ &&
            pellets_ == b.pellets_ &&
            power_pellets_ == b.power_pellets_ &&
            spawn_points_ == b.spawn_points_ &&
            num_pellets_ == b.num_pellets_);
}

bool
Maze::operator!=(Maze b)
{
    return !(*this == b);
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