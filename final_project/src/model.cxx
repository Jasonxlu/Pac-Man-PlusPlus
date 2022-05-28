#include "model.hxx"

using namespace ge211;

Model::Model()
        :
        pacman Pacman(),

          //initialize characters here
{
    //
}

/// PUBLIC FUNCTIONS (TODO: I think some of these can be private. Just making
/// them public to start off with.)


/// Determines whether the character hits the side of the screen
bool Model::character_hits_screen_wall() {

}

/// Determines whether the character hits the a maze wall
bool Model::character_hits_maze_wall() {

}

// Helper function for character_hits_maze_wall and character_hits_screen_wall
bool Model::hits_wall() {

}

void
Model::on_frame(double dt)
{

}

/// Sets round over
void
Model::set_round_over(bool over) {

}

/// Sets game over
void
Model::set_game_over() {

}

/// This is called if the Pacman hits a ghost.
/// Returns true if the Pacman killed the ghost
/// Returns false if the Pacman dies.
bool Model::overlaps_ghost() {

}

/// removes a life from Pacman and sets game_over if < 0
void Model::kill_pacman() {

}

/// kills a ghost. Puts it back in the cage
void Model::kill_ghost(Ghost ghost) {

}

/// maze[pacman position] = regular pellet --> checks if maze num_pellets
/// = 0. If so, it ends the round.
/// if it's a power pellet, sets pacman is_powered and sets power timer.
/// calls maze.hit_pellet(maze position) in both cases.
void Model::overlaps_pellet() {

}

/// PRIVATE FUNCTIONS


