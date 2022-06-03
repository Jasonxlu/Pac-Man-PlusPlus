#include <ge211.hxx>

#include "ghost.hxx"
#include "pacman.hxx"
#include "maze.hxx"
#include "tile.hxx"


#include <iostream>

#include <vector>

using Block = ge211::Rect<int>;

using namespace ge211;

class Model
{

    /// PRIVATE FUNCTIONS
private:


    /// PUBLIC FUNCTIONS

public:

    Model();

    Model(int width, int height, int maze_size);
    //Jason: TODO Right here
    //initialize characters here
    //Brennan comment: changed the constructor to be in cxx file

    void update_pacman_direction(Dimensions d);

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

    /// This asks if the pacman hits a ghost.
    bool pacman_overlaps_ghost(Pacman p, Ghost g);

    /// removes a life from Pacman and sets game_over if < 0
    void kill_pacman() {};

    /// kills a ghost. Puts it back in the cage
    void kill_ghost(Ghost ghost) {};

    // Converts a concrete screen (pixel) position to an abstract board
    // position.
    ge211::Posn<int>
    screen_to_board_(ge211::Posn<int> screen_pos) const;

    // Converts an abstract board position to a concrete screen
    // position.
    ge211::Posn<int>
    board_to_screen(ge211::Posn<int> board_pos) const;

    /// maze[pacman position] = regular pellet --> checks if maze num_pellets
    /// = 0. If so, it ends the round.
    /// if it's a power pellet, sets pacman is_powered and sets power timer.
    /// calls maze.hit_pellet(maze position) in both cases.
    void overlaps_pellet() {};

    Maze maze_() const;

    Pacman get_pacman() const {
        return pacman_;
    }
    Ghost get_ghost1() const {
        return g1_;
    }
    Ghost get_ghost2() const {
        return g2_;
    }
    Ghost get_ghost3() const {
        return g3_;
    }
    Ghost get_ghost4() const {
        return g4_;
    }


    /// PRIVATE VARIABLES
private:

    bool game_over_;
    Maze m_;
    Pacman pacman_;

    //Dimensions screen_dims;

    Ghost g1_;
    Ghost g2_;
    Ghost g3_;
    Ghost g4_;

    std::vector<ge211::Posn<int>> maze_walls_;

    int maze_size_;

    ///PUBLIC VARIABLES
public:
    // A source of random “boost” values.
    ge211::Random_source<int> random_direction_source;
};