#include <ge211.hxx>
#include "model.hxx"
#include "ghost.hxx"
#include "tile.hxx"
#include <catch.hxx>


//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//

//5 significant model tests

struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Model&);
    // Sets the player at `posn` to `tile`.
    void set_tile(ge211::Posn<int> posn, Tile t);

    Tile get_tile(ge211::Posn<int> posn);

    // Gives direct access to `model.g1_` so our tests can modify it:
    Ghost& get_ghost_1();

    void set_ghost_1(Ghost g);

    Pacman& get_pacman();

    int get_score();
};

//Test #1: pacman eats a power pellet and can kill ghosts,
//But then dies when a ghost hits it after a certain amount of time.
TEST_CASE("Test #1: power pellet + dying")
{
    /*
    ///
    /// SETUP
    ///

    Model model(24,16, 32);
    Test_access access(model);

    // Let's run at 8 fps.
    double const dt = 0.125;


    ///
    /// TEST OPERATION
    ///

    Position initial_pac_pos = model.get_pacman().get_position();

    Ghost ghost_to_die (initial_pac_pos.right_by(
                      model.get_pacman().get_dimensions().width+10
    ));
    //new ghost that is 5 pixels away from the pacman.
    model.set_ghost(1, ghost_to_die);
    access.get_pacman().update_direction({1,0});
    //make the pacman move left

    CHECK(
            access.get_ghost_1().get_position() == Posn<float>{385,322}
    );


    ///
    /// CHECKS
    ///

    model.on_frame(dt);

    CHECK( //ghost not vulnerable
            !access.get_ghost_1().is_vulnerable()
    );

    CHECK(
            access.get_ghost_1().get_position() == Posn<float>{385,322});

    model.on_frame(dt); //now pac hits ghost and dies


    //reset ghost position and pac position
    CHECK(
            access.get_ghost_1().get_position() == Posn<float>{375.625,322}
    );
    CHECK(
        access.get_pacman().get_position() == initial_pac_pos
        );


    //place a power pellet right on top of the pacman.
    access.set_tile({11,10},Tile::power_pellet);


    model.on_frame(dt); //pac eat power pellet
    model.on_frame(dt);

    CHECK( //ate pellet
            access.get_tile({11,10}) == Tile::path
    );
    CHECK( //ate pellet
            access.get_ghost_1().is_vulnerable()
    );

    model.on_frame(dt);

    CHECK( //ate power pellet so now it just eats the ghost
            access.get_pacman().get_position() != initial_pac_pos
    );
    CHECK( //ate pellet
            access.get_ghost_1().get_position() == initial_pac_pos.right_by(
            model.get_pacman().get_dimensions().width)
    );


*/
}

//Test #2: round increments and game updates after all pellets eaten
TEST_CASE("Test #2: Round Increments after all the pellets are eaten")
{
    Model model(24,16, 32);
    Test_access access(model);
    Maze m = model.get_maze();

    // Let's run at 8 fps.
    double const dt = 0.125;

    // Simulates the eating of pellets
    for(int x = 0; x<24; x++)
    {
        for(int y = 0; y<16; y++)
        {
            switch(m[{x,y}])
            {
                case Tile::wall:
                    access.set_tile({x,y},Tile::path);
                    break;
                case Tile::pellet:
                    access.set_tile({x,y},Tile::path);
                    m.dec_num_pellets();
                    break;
                case Tile::power_pellet:
                    access.set_tile({x,y},Tile::path);
                    m.dec_num_pellets();
                    break;
                case Tile::path:
                    break;
                case Tile::spawn_point:
                    break;
            }
        }
    }
    int expected_rn = model.get_round_number();
    //Checking to see if pellets are 0
    CHECK(m.get_pellets() == 0);

    //Checks to see if round number is updated
    CHECK(model.get_round_number() == expected_rn);

}

//Test #3: pacman cannot go through walls.
TEST_CASE("#3 Pacman stops at walls")
{
    Model model(24,16, 32);
    Test_access access(model);

    // Let's run at 8 fps.
    double const dt = 0.125;

    // Get the Pac-Man's current location as the expected
    ge211::Posn<float> expected_pos = access.get_pacman().get_position();

    //Update the frame and move the Pacman upward towards the wall
    access.get_pacman().update_direction({0,1});

    //Get the updated position of the Pac-man (Should remain the same as
    // expected)
    ge211::Posn<float> pos = access.get_pacman().get_position();

    //Check that the Pac-man has not moved due to collision with a wall
    CHECK(pos == expected_pos);

}

//Test #4: score increases when pacman eats a pellet, a power pellet, or a
// ghost.
TEST_CASE("#4 Score increases when pacman eats a pellet, a power pellet, or a "
          "ghost.") {
    ///
    /// SETUP
    ///

    Model model(24,16, 32);
    Test_access access(model);

    // Let's run at 8 fps.
    double const dt = 0.125;


    ///
    /// TEST OPERATION
    ///

    //place a power pellet right on top of the pacman.
    access.set_tile({11,10},Tile::power_pellet);
    Ghost ghost_to_die (model.get_pacman().get_position().right_by(
            model.get_pacman().get_dimensions().width/2+20
    ));
    //new ghost that is 5 pixels away from the pacman.
    access.set_ghost_1(ghost_to_die);
    access.get_pacman().update_direction({0,1});
    //make the pacman move left


    ///
    /// CHECKS
    ///

    model.on_frame(dt); //make pacman eat power pellet
    model.on_frame(dt);

    CHECK( //ghost vulnerable
            access.get_ghost_1().is_vulnerable()
    );
    CHECK( //ate power pellet --> raise score by 50
            access.get_score() == 50
    );
    CHECK(
            access.get_tile({11,10}) == Tile::path
    );

    model.on_frame(dt);
    model.on_frame(dt);
    model.on_frame(dt);

    // Simulate one frame in which the pacman hits the ghost,
    CHECK( //ate ghost --> raise score by 200
            access.get_score() == 250
    );
    CHECK( //ghost eaten --> still longer vulnerable
            access.get_ghost_1().is_vulnerable()
    );
    access.get_pacman().set_velocity(0);
    access.set_tile({11,10},Tile::pellet);

    model.on_frame(dt);
    model.on_frame(dt);

    // Simulate one frame in which the pacman eats the pellet,
    CHECK( //ate ghost --> raise score by 200
            access.get_score() == 260
    );
    CHECK(
            access.get_tile({11,10}) == Tile::path
    );

}

//Test #5: Pacman loses lives and the game ends when pacman's lives = 0.
TEST_CASE("Pac-man Dies, Game over") {

    ///
    /// SETUP
    ///

    Model model(24,16, 32);
    Test_access access(model);

    // Let's run at 8 fps.
    double const dt = 0.125;


    ///
    /// TEST OPERATION
    ///

    Ghost killer_ghost (model.get_pacman().get_position().right_by(
            model.get_pacman().get_dimensions().width/2+10
    ));
    //new ghost that is 5 pixels away from the pacman.
    access.set_ghost_1(killer_ghost);
    access.get_pacman().update_direction({0,0});
    //make the pacman not move


    ///
    /// CHECKS
    ///
    CHECK(model.get_pacman_lives() == 3);

    model.on_frame(dt);

    //ghost kills pacman
    CHECK(model.get_pacman_lives() == 2);

    ///
    /// TEST OPERATION
    ///

    Ghost killer_ghost2 (model.get_pacman().get_position().right_by(
            model.get_pacman().get_dimensions().width/2+10
    ));
    //new ghost that is 5 pixels away from the pacman.
    access.set_ghost_1(killer_ghost2);


    ///
    /// CHECKS
    ///
    CHECK(model.get_pacman_lives() == 2);

    model.on_frame(dt);

    //ghost kills pacman
    CHECK(model.get_pacman_lives() == 1);

    ///
    /// TEST OPERATION
    ///

    Ghost killer_ghost3 (model.get_pacman().get_position().right_by(
            model.get_pacman().get_dimensions().width/2+10
    ));
    //new ghost that is 5 pixels away from the pacman.
    access.set_ghost_1(killer_ghost3);


    ///
    /// CHECKS
    ///
    CHECK(model.get_pacman_lives() == 1);

    model.on_frame(dt);

    //ghost kills pacman
    CHECK(model.get_pacman_lives() == 0);

    CHECK(model.game_over()); //should be game over now

}



///
/// Member function definitions for Test_access
///

Test_access::Test_access(Model& model)
        : model(model)
{ }

void
Test_access::set_tile(ge211::Posn<int> posn, Tile t)
{
    model.m_[posn] = t;
}

Ghost&
Test_access::get_ghost_1()
{
    return model.g1_;
}

void
Test_access::set_ghost_1(Ghost g) {
    model.g1_ = g;
}

Pacman&
Test_access::get_pacman()
{
    return model.pacman_;
}
int
Test_access::get_score()
{
    return model.score_;
}
Tile
Test_access::get_tile(ge211::Posn<int> posn)
{
    return model.m_[posn];
}
