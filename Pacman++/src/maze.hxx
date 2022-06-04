#pragma once

#include <ge211.hxx>
#include <position_set.hxx>
#include <vector>
#include <tile.hxx>

#include <algorithm>
#include <random>

class Maze {

public:

    /// Jason: Aliasing

    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    //using Rectangle = ge211::Rect<int>;

    // Defined and documented below.
    class reference;

private:
    Dimensions dims_;
    void bounds_check_(Position where) const;

    Position_set walls_;
    Position_set pellets_;
    Position_set power_pellets_;
    Position_set spawn_points_;
    int num_pellets_;
    // INVARIANT: (walls_ & pellets_ & power_pellets_).empty()


    //
    // PRIVATE HELPER FUNCTION MEMBERS
    //

    Tile get_(Position where) const;
    void set_(Position where, Tile who);

public:
    explicit Maze(Dimensions dims);

    /// Returns the same `Dimensions` value passed to the
    /// constructor.
    Dimensions dimensions() const;

    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;

    /// Returns the tile stored at the given position
    ///
    /// ## Errors
    ///
    ///  - throws `ge211::Client_logic_error` if `!good_position(pos)`.
    Tile operator[](Position pos) const;


    /// Returns a reference to the `Tile` stored at `pos`. This can
    /// be assigned to update the maze.
    ///
    /// ## Errors
    ///
    ///  - throws `ge211::Client_logic_error` if `!good_position(pos)`.
    reference operator[](Position pos);

    std::vector<Position> get_maze_walls(); //TODO: overhaul? Maybe it's ok
    std::vector<Position> get_maze_pellets();


    /// Sets the given position to a path.
    /// Can be used to "destroy" pellets and power pellets!
    void destroy_pellet(Position p);


    /// Returns a reference to a `std::vector` containing all four "unit
    /// direction vectors".
    static std::vector<Dimensions> all_directions();

    void set_pellets();

    bool all_pellets_eaten();

    int get_pellets()
    {
        return num_pellets_;
    }

    void dec_num_pellets()
    {
        num_pellets_--;
    }

    bool
    operator==(Maze b);

    bool
    operator!=(Maze b);


};



//HELPER CLASS
/// Class returned by `operator[](Position)` that simulates
/// an assignable reference to a `Posn<int>`. This is what allows
/// you to write
///
///     maze[pos] = wall;
///
/// to place `wall` at `pos`.
///
/// The definition of the class follows this definition of the
/// `Maze` class.
class Maze::reference
{
    Maze& maze_;
    Position pos_;

public:
    /// Assigns the value of `that` to the object of `this`.
    reference& operator=(reference const&) noexcept;

    /// Assigns to the object of the reference.
    reference& operator=(Tile) noexcept;

    /// Returns the value of the reference.
    operator Tile() const noexcept;


private:
    friend class Maze;

    reference(Maze&, Position) noexcept;
};