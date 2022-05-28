#pragma once

#include <ge211.hxx>

#include "board.hxx"


class Model
{
public:


    ///
    /// CONSTRUCTOR
    ///

    //
    explicit Model(
            );

    // Specifying variables
    explicit Model(
            ge211::Dims<int> maze_dimensions,
            );


    /// Determines whether the character hits the side of the screen
    bool character_hits_screen_wall();

    /// Determines whether the character hits the a maze wall
    bool character_hits_maze_wall();

    /// Helper function for character_hits_maze_wall
    /// and character_hits_screen_wall
    bool hits_wall();

    void on_frame(double dt);

    /// Sets round over
    void set_round_over(bool over);

    /// Sets game over
    void set_game_over();

    /// This is called if the Pacman hits a ghost.
    /// Returns true if the Pacman killed the ghost
    /// Returns false if the Pacman dies.
    bool overlaps_ghost();

    /// removes a life from Pacman and sets game_over if < 0
    void kill_pacman();

    /// kills a ghost. Puts it back in the cage
    void kill_ghost(Ghost ghost);

    /// maze[pacman position] = regular pellet --> checks if maze num_pellets
    /// = 0. If so, it ends the round.
    /// if it's a power pellet, sets pacman is_powered and sets power timer.
    /// calls maze.hit_pellet(maze position) in both cases.
    void overlaps_pellet();


private:
    ///
    /// VARIABLES
    ///

    int player_score_;
    /// the amount of points the player has. The player gains points when the
    /// Pacman eats a ghost or a pellet.
    /// The score bonus for each should reflect the round number.

    int player_lives_ = 3;
    /// The amount of lives the player has left.
    /// This is initialized to 3.
    /// The game ends when this reaches 0.

    bool is_round_over_ = false;
    /// This will be true in the time between each round.

    bool is_game_over_ = false;
    /// This will be true when the player runs out of lives.

    Maze maze_;
    /// TODO: Maze

    double pacman_powered_time_remaining_;
    /// The amount of seconds remaining that the pacman is powered up
    double pacman_powered_time_total_ = 10;
    /// The amount of time the pacman is powered up after it eats a power
    /// pellet.

    double ghost_cage_release_time_remaining_;
    /// The amount of seconds remaining that a ghost can be released
    double ghost_cage_release_time_total_ = 10;
    /// The amount of seconds between ghost releases.

    int round_counter_ = 1;
    /// The number round the player is on. This is 1-indexed.

    Pacman pacman_;


};
