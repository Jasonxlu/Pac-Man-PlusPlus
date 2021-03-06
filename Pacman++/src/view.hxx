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

    Transform get_transform_pacman(Dimensions);

    // Converts an abstract board position to a concrete screen
    // position.
    Position
    board_to_screen(ge211::Posn<int> board_pos) const;

    // Converts a concrete screen (pixel) position to an abstract board
    // position.
    ge211::Posn<int>
    screen_to_board(Position screen_pos) const;

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_;

    // Jason: Adding Sprites
    ge211::Image_sprite pacman;
    ge211::Image_sprite wall;
    ge211::Image_sprite ghost1;
    ge211::Image_sprite ghost2;
    ge211::Image_sprite ghost3;
    ge211::Image_sprite ghost4;
    ge211::Font sans30;
    ge211::Font sans30_massive;
    ge211::Image_sprite pellet;
    ge211::Text_sprite score;
    ge211::Text_sprite lives;
    ge211::Text_sprite round;
    ge211::Text_sprite game_over;
    ge211::Image_sprite ghostv;
    ge211::Image_sprite ghost1nv;
    ge211::Image_sprite ghost2nv;
    ge211::Image_sprite ghost3nv;
    ge211::Image_sprite ghost4nv;
    ge211::Image_sprite pacman_ate;
    ge211::Image_sprite pacman_orig;


};
