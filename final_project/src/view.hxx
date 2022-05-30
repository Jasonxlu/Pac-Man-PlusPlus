#pragma once

#include "model.hxx"
#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;

    // Jason: Adding Sprites
    ge211::Circle_sprite pacman;
    ge211::Circle_sprite ghost1;
    ge211::Circle_sprite ghost2;
    ge211::Circle_sprite ghost3;
    ge211::Circle_sprite ghost4;
    ge211::Rectangle_sprite wall;


};
