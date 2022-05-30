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
Character
Character::next(double dt) {
    Character result(*this);
    result.position_ = result.position_ + dt*result.direction_.into<float>()
                                          *result.velocity_;
    return result;
}