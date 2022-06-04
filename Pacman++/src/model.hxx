#include <ge211.hxx>

#include "ghost.hxx"
#include "pacman.hxx"
#include "maze.hxx"
#include "tile.hxx"
#include "position_set.hxx"


#include <iostream>

#include <vector>

using Block = ge211::Rect<int>;

using namespace ge211;

class Model
{


#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif


    /// PUBLIC FUNCTIONS

public:


    Model(int width, int height, int maze_size);
    //initialize characters here
    //Brennan comment: changed the constructor to be in cxx file

    void update_pacman_direction(Dimensions d);


    /// Determines whether the character hits the a maze wall
    bool
    character_hits_maze_wall(Character c);

    void
    on_frame(double dt);

    /// Sets round over and increments the round #.
    void increment_round();

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
    bool pacman_overlaps_pellet();

    bool  game_over() const{
        //returns whether or not the game is over (for the view)
        return game_over_;
    }

    Maze const& maze_() const {
        return m_;
    }
    Pacman get_pacman() const {
        return pacman_;
    }
    Pacman const& pacman() const {
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


    ///getters
    int get_score() const {
        return score_;
    }
    int get_round_number() const { //for the view. Adding + 1 because it
        // should start at 1.
        return round_number_ + 1;
    }
    int get_pacman_lives() const {
        return pacman_lives_;
    }

    void reset_maze_change();
    void set_level(int lvl);


    void decrement_pacman_lives();
    void increment_score(int i);

    ///TESTING FUNCTIONS
    void set_tile(Position p, Tile t) {
        m_[p.into<int>()] = t;
    }
    void set_ghost(int num_ghost, Ghost g) {
        switch(num_ghost) {
        case 1:
            g1_ = g;
        case 2:
            g2_ = g;
        case 3:
            g3_ = g;
        case 4:
            g4_ = g;
        }
    }

    Maze get_maze()
    {
        return m_;
    }


    /// PRIVATE VARIABLES
private:

    bool game_over_;
    Maze m_;
    Pacman pacman_;

    std::vector<Maze> mazes_;

    //Dimensions screen_dims;

    Ghost g1_;
    Ghost g2_;
    Ghost g3_;
    Ghost g4_;

    std::vector<ge211::Posn<int>> maze_walls_;

    int maze_size_;
    int score_ = 0;
    int round_number_ = 0;
    int pacman_lives_ = 3;
    int pellet_score_ = 10;
    int power_pellet_score_ = 50;
    int ghost_score_ = 200;
    static int round_num;
    static bool ate;

    ///PUBLIC VARIABLES
public:
    // A source of random “boost” values.
    ge211::Random_source<int> random_direction_source;
    static void set_round_num(int lvl) {
        round_num = lvl;
    }
    static bool get_ate()
    {
        return ate;
    }

    void set_maze(Maze m)
    {
        m_ = m;
    }

};