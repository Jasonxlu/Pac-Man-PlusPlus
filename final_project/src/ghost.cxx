//
// Created by Jason L on 5/30/22.
//

#include "ghost.hxx"

Ghost::Ghost() :
        Character({50,50}, 10,
                  10, {1,0}, 50),
        vulnerable_(false),
        alive_(true),
        timer_(0)
{
    //call parent constructor in initializer list
}


void
Ghost::set_vulnerable(bool vulnerable) {
    vulnerable_ = vulnerable;
}

void Ghost::set_alive(bool alive)
{
    alive_ = alive;
    if(!alive) { //set alive to false (kill ghost)
        velocity_=0;
        direction_ = {0,-1}; //go up
        position_={100,100};
    }
    timer_ = 0;
}


void Ghost::update_timer(float dt) {
    timer_ += dt;
    if(timer_ >= timer_respawn_threshold_) {
        timer_ = 0;
        alive_ = true;
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
Ghost::hit_wall(Maze m) {
    //check which directions are safe to move in.
    //set the direction to be equal to a safe direction.

    //pacman direction stuff
    //Position position_diff = position_.right_by(pacman_position.x)
    //        .down_by(pacman_position.y);
    //Not sure what's going on here, it doesn't like:
    //Position position_diff = position_ - pacman_position;

    //cast the position to int to check it against the
    ge211::Posn<int> current_maze_position = position_.into<int>();
    std::vector<Maze::Dimensions> possible_directions =
            m.all_directions_randomized();

    for(Dimensions d : possible_directions) {
        if(//m[current_maze_position + d] &&
        // TODO: maybe ask if this position is in the set before questioning
            m[current_maze_position + d] == Tile::wall) {
            //check moving in that direction.
            direction_ = d; //if moving in that direction is ok, set the
            // direction to that direction.
        }
    }

}