//
// Created by Jason L on 5/30/22.
//
#pragma once

#include <ge211.hxx>
#include <character.hxx>
#include <maze.hxx>

class Ghost : public Character {

private:
    bool vulnerable_;
    bool alive_;
    float timer_; //timer until this ghost can respawn.

public:

    ///constructor
    Ghost();

    void set_alive(bool alive);

    void set_vulnerable(bool vulnerable);

    bool is_vulnerable();

    Ghost next(double dt);

    void hit_wall(Maze m);

};
