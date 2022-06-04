//
// Created by Jason L on 5/30/22.
//
#pragma once

#include <ge211.hxx>
#include <character.hxx>
#include <maze.hxx>

class Ghost : public Character {

private:
    float vulnerable_velocity_;
    bool vulnerable_;
    bool alive_;
    float timer_alive_; //timer until this ghost can respawn.
    float timer_vulnerable_; //timer until this ghost is no longer vulnerable
    float timer_respawn_threshold_ = 20;
    float timer_vulnerable_threshold_ = 20;
    //20 seconds (or whatever it is) until respawn
    float base_velocity_ = 125;
    Position spawn_position_;

public:

    ///constructor
    Ghost();

    Ghost(Position initial_position);

    void set_alive(bool alive);

    void set_vulnerable(bool vulnerable);

    void update_timer(float dt);

    bool is_vulnerable();

    Ghost next(double dt);

    void hit_wall(Maze m, int random_int_bounded,
                  ge211::Posn<int> current_maze_posn);


    /// Compares two `Ghost`s for equality. This may be useful for testing.
    ///
    /// Two `Ghost`s are equal if all their member variables are pairwise
    /// equal.
    bool
    operator==(Ghost b);

    /// Inequality for `Ball`s.
    bool
    operator!=(Ghost b);
};
