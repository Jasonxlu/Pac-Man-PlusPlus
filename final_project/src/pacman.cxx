//
// Created by Jason L on 5/30/22.
//

#include "pacman.hxx"

Pacman::Pacman() :
        Character({0,0}, 10,
                  10, {0,0}, 0),
                  is_powered_(false),
                  alive_(true)
{
    //call parent constructor in initializer list
}


void
Pacman::set_powered(bool powered) {
    is_powered_ = powered;
}

bool Pacman::overlaps_ghost(Ghost g) {
    //right side of pacman < left side of ghost OR
    //right side of ghost < left side of pacman OR
    //bottom of pacman > top of ghost OR
    //bottom of ghost > top of pacman
    //TODO: Might be wrong
    return !( (position_.x+width_ < g.get_position().x-
            g.get_dimensions().width) ||
              (g.get_position().x+g.get_dimensions().width < position_
              .x-width_) ||
              (position_.y-height_ > g.get_position().y+g.get_dimensions()
              .height/2) ||
              (g.get_position().y-g.get_dimensions().height > position_
              .y+height_) );
}

bool Pacman::hit_ghost(Ghost g) {
    if(g.is_vulnerable()) {
        g.set_alive(false);
        return true;
    } else {
        alive_ = false;
        return false;
    }

}


Pacman
Pacman::next(double dt) {
    Pacman result(*this);
    result.position_ = result.position_ + dt*result.direction_.into<float>()
                                          *result.velocity_;
    return result;
}