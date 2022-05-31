//
// Created by Jason L on 5/30/22.
//

#pragma once

#include <character.hxx>
#include <ge211.hxx>
#include <ghost.hxx>

class Pacman : public Character
{

private:
    bool is_powered_;
    bool alive_;

public:

    ///constructor
    Pacman();

    void set_powered(bool powered);

    bool hit_ghost(Ghost g);

    Pacman next(double dt);

    bool overlaps_ghost(Ghost g);

};
