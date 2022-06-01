//
// Created by Jason L on 5/30/22.
//
//
// Created by thebr on 5/26/2022.
//

#include "character.hxx"

Character::Character(Position initial_position, float height, float width,
                     Dimensions direction, float velocity) :
        position_(initial_position),
        height_(height),
        width_(width),
        direction_(direction),
        velocity_(velocity)
{


}


/// Returns the state of the character after `dt` seconds have passed,
/// were it to move freely (without obstacles). Thus, the result is
/// a new character just like this one but whose position has been
/// updated based on its current velocity and the given time
/// interval `dt`. (This is an application of the equation relating
/// distance to velocity and time: *Δd = v ⋅ Δt*.)
///
/// This function is useful because the model's algorithm for
/// collision detection involves speculatively moving the character and
/// checking where it would end up, before actually moving it.
///
/// This can also be used to actually move it, via assignment:
///
///    character = character.next();
///

//Brennan comment: I don't know if we need this
/*
Character
Character::next(double dt) {
    Character result(*this);
    result.position_ = result.position_ + dt*result.direction_.into<float>()
                                          *result.velocity_;
    return result;
}
 */

Position Character::get_position()
{
    return position_;
}

Dimensions Character::get_dimensions() {
    return {width_, height_};
}

bool Character::hits_maze_wall(const Block& block)
{
    //right side of ball < left side of block OR
    //right side of block < left side of ball OR
    //bottom of ball > top of block OR
    //bottom of block > top of ball
    return !( (position_.x+width_ < block.center().x-block.width/2) ||
              (block.center().x+block.width/2 < position_.x-width_) ||
              (position_.y-height_ > block.center().y+block.height/2) ||
              (block.center().y-block.height/2 > position_.y+height_) );
}

void
Character::set_velocity(float v) {
    velocity_ = v;
}