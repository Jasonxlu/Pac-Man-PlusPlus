//
// Created by Jason L on 5/30/22.
//

#include "ghost.hxx"

Ghost::Ghost() :
        Character({50,50}, 10,
                  10, {0,0}, 0),
        is_vulnerable_(false),
        alive_(true)
{
    //call parent constructor in initializer list
}


void
Ghost::set_vulnerable(bool vulnerable) {
    is_vulnerable_ = vulnerable;
}

void Ghost::set_alive(bool alive)
{
    alive_ = alive;
}
