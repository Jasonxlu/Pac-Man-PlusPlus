//
// Created by Jason L on 5/30/22.
//

#pragma once
#include <ge211.hxx>

#include <character.hxx>
#include <ghost.hxx>

class Pacman : public Character
{

private:
    bool alive_;

public:

    ///constructor
    Pacman();
    explicit Pacman(Position initial_position);

    bool hit_ghost(Ghost g);

    Pacman next(double dt);

    bool overlaps_ghost(Ghost g);

    void update_direction(Dimensions d);


};
