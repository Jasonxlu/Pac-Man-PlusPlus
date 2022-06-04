//
// Created by Jason L on 5/30/22.
//

#include "ghost.hxx"

Ghost::Ghost() :
        Ghost({400,250})
{
    //call parent constructor in initializer list
}
//
Ghost::Ghost(Position initial_position) :
        Character(initial_position, 30,
                  30, {1,0}, 75),
        vulnerable_velocity_(50),
        vulnerable_(false),
        alive_(true),
        timer_alive_(0),
        timer_vulnerable_(0),
        spawn_position_(initial_position)
{
    //call parent constructor in initializer list
}


void
Ghost::set_vulnerable(bool vulnerable) {
    vulnerable_ = vulnerable;
    if(vulnerable) { //set vulnerable to true
        velocity_ = vulnerable_velocity_;
    }
    timer_vulnerable_ = 0;
}

void Ghost::set_alive(bool alive)
{
    alive_ = alive;
    if(!alive) { //set alive to false (kill ghost)
        velocity_=0;
        direction_ = {0,-1}; //go up
        position_=spawn_position_;
    }
    timer_alive_ = 0;
}


void Ghost::update_timer(float dt) {
    if(!alive_) {
        timer_alive_ += dt;
    }
    if(vulnerable_) {
        timer_vulnerable_ += dt;
    }
    if(timer_alive_ >= timer_respawn_threshold_) {
        timer_alive_ = 0;
        alive_ = true;
        velocity_ = base_velocity_;
    }
    if(timer_vulnerable_ >= timer_vulnerable_threshold_) {
        timer_vulnerable_ = 0;
        vulnerable_ = false;
        velocity_ = base_velocity_;
    }
}

bool Ghost::is_vulnerable()
{
    return vulnerable_;
}

Ghost
Ghost::next(double dt) {
    update_timer(dt);
    Ghost result(*this);
    result.position_ = result.position_ + dt*result.direction_.into<float>()
                                          *result.velocity_;
    return result;
}


void
Ghost::hit_wall(Maze m, int random_int_bounded, ge211::Posn<int>
        current_maze_posn) {

    //check which directions are safe to move in.
    //set the direction to be equal to a safe direction.

    //pacman direction stuff
    //Position position_diff = position_.right_by(pacman_position.x)
    //        .down_by(pacman_position.y);
    //Not sure what's going on here, it doesn't like:
    //Position position_diff = position_ - pacman_position;

    std::vector<Dimensions> possible_directions =
            m.all_directions();

    std::vector<Dimensions> possible_directions_randomized;

    //randomize based on random_int_bounded
    //NOT ACTUALLY RANDOMIZED - it will be in the same order,
    //just seeded differently.
    for(int i = 0; i < 4; i++) {
        possible_directions_randomized.push_back(
                possible_directions[
                        (random_int_bounded+i)%4
                ]
        );
    }

    for(Dimensions d : possible_directions_randomized) {
        if(m[current_maze_posn + d] != Tile::wall) {
            //check moving in that direction.
            direction_ = d; //if moving in that direction is ok, set the
            // direction to that direction.
        }
    }

}



bool
Ghost::operator==(Ghost b)
{
    return (vulnerable_velocity_ == b.vulnerable_velocity_ &&
        vulnerable_ == b.vulnerable_ &&
        alive_ == b.alive_ &&
        timer_alive_ == b.timer_alive_ &&
        timer_vulnerable_ == b.timer_vulnerable_ &&
        position_ == b.position_ &&
        height_ == b.height_ &&
        width_ == b.width_ &&
        direction_ == b.direction_ &&
        velocity_ == b.velocity_
    );
}

bool
Ghost::operator!=(Ghost b)
{
    return !(*this == b);
}