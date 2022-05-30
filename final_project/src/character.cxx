//
// Created by thebr on 5/26/2022.
//

#include "character.hxx"

Character::Character(Position initial_position) :
        position_(initial_position)
{


}

/// Returns the position of the top-left corner of the ball's
/// "bounding box", meaning the smallest rectangle in which is can
/// be enclosed. This is useful to the UI because sprites are
/// positioned based on their top-left corners.
Character::Position top_left();


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
Character next(double dt);