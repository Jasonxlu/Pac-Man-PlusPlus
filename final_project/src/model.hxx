#include <ge211.hxx>

#include "ghost.hxx"

#include <iostream>

#include <vector>

using namespace ge211;

class Model
{


    /// PUBLIC FUNCTIONS (TODO: I think some of these can be private. Just making
    /// them public to start off with.)

public:

    Model()
    //Jason: TODO Right here
    //initialize characters here
    {

    }

    /// Determines whether the character hits the side of the screen
    //Jason: TODO: Boolean values are placeholders right now
    bool
    character_hits_screen_wall() {return true;}

    /// Determines whether the character hits the a maze wall
    bool
    character_hits_maze_wall() {return true;}

    // Helper function for character_hits_maze_wall and character_hits_screen_wall
    bool
    hits_wall() {return true;}

    void
    on_frame(double dt) {}

    /// Sets round over
    void
    set_round_over(bool over) {}

    /// Sets game over
    void
    set_game_over() {}

    /// This is called if the Pacman hits a ghost.
    /// Returns true if the Pacman killed the ghost
    /// Returns false if the Pacman dies.
    bool overlaps_ghost() {return true;}

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

};