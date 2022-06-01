#pragma once

#include <ge211.hxx>
#include <vector>

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
    using Rectangle = ge211::Rect<int>;

private:
    Dimensions dims_;
    std::vector<Rectangle> walls_;
    bool get_(Position where) const;
    void bounds_check_(Position where) const;

public:
    explicit Maze(Dimensions dims);

    /// Returns the same `Dimensions` value passed to the
    /// constructor.
    Dimensions dimensions() const;

    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;

    /// Returns true if no wall is stored at `pos`, false otherwise.
    ///
    /// ## Errors
    ///
    ///  - throws `ge211::Client_logic_error` if `!good_position(pos)`.
    bool operator[](Position pos) const;

    std::vector<Rectangle>
    get_walls();


    /// Returns a reference to a `std::vector` containing all four "unit
    /// direction vectors".
    static std::vector<Dimensions> const& all_directions_randomized();


};