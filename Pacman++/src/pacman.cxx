//
// Created by Jason L on 5/30/22.
//

#include "pacman.hxx"

Pacman::Pacman() :
        Pacman({200,200})
{
    //call parent constructor in initializer list
}

Pacman::Pacman(Position initial_position) :
        Character(initial_position, 21,
                  23, {0,0}, 0),
        alive_(true)
{
    //call parent constructor in initializer list
}

bool Pacman::overlaps_ghost(Ghost g) {
    //right side of pacman < left side of ghost OR
    //right side of ghost < left side of pacman OR
    //bottom of pacman > top of ghost OR
    //bottom of ghost > top of pacman
    //TODO: Might be wrong

    return !( (position_.x+width_ < g.get_position().x) ||
              (g.get_position().x+g.get_dimensions().width < position_.x) ||
              (position_.y-height_ > g.get_position().y) ||
              (g.get_position().y-g.get_dimensions().height > position_.y) );
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

void
Pacman::update_direction(Dimensions d) {
    direction_ = d;
    velocity_ = 150;
}