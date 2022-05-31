//
// Created by Jason L on 5/30/22.
//
#pragma once

#include <ge211.hxx>
#include <character.hxx>

class Ghost : public Character {

private:
    bool is_vulnerable_;
    bool alive_;

public:

    ///constructor
    Ghost();

    void set_alive(bool alive);

    void set_vulnerable(bool vulnerable);

};
