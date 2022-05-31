#include <ge211.hxx>

#include "ghost.hxx"
#include "pacman.hxx"

#include <iostream>

#include <vector>

using Block = ge211::Rect<int>;

using namespace ge211;

class Model
{


    /// PUBLIC FUNCTIONS (TODO: I think some of these can be private. Just making
    /// them public to start off with.)

public:

    Model();
    //Jason: TODO Right here
    //initialize characters here
    //Brennan comment: changed the constructor to be in cxx file

    /// Determines whether the character hits the side of the screen
    //Jason: TODO: Boolean values are placeholders right now
    bool
    character_hits_screen_wall(Character c);

    /// Determines whether the character hits the a maze wall
    bool
    character_hits_maze_wall(Character c);

    void
    on_frame(double dt);

    /// Sets round over
    void
    set_round_over(bool over);

    /// This asks if the pacman overlaps a ghost
    bool pacman_overlaps_ghost(Pacman p, Ghost g);

    /// removes a life from Pacman and sets game_over if < 0
    void kill_pacman() {}

    /// kills a ghost. Puts it back in the cage
    void kill_ghost(Ghost ghost) {}

    /// maze[pacman position] = regular pellet --> checks if maze num_pellets
    /// = 0. If so, it ends the round.
    /// if it's a power pellet, sets pacman is_powered and sets power timer.
    /// calls maze.hit_pellet(maze position) in both cases.
    void overlaps_pellet() {}

    /// PRIVATE FUNCTIONS

private:

    bool game_over_;
    Maze m_;
    Pacman pacman_;

    Ghost g1_;
    Ghost g2_;
    Ghost g3_;
    Ghost g4_;
};