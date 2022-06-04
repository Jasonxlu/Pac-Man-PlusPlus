
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
    // Gives direct access to `model.g1_` so our tests can modify it:
    Ghost& get_ghost_1();

    void set_ghost_1(Ghost g);

    Pacman& get_pacman();

    int get_score();
};

//Test #1: pacman eats a power pellet and can kill ghosts,
//But then dies after a certain amount of time.
TEST_CASE("Test #1: power pellet + dying")
{
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
            model.get_pacman().get_dimensions().width/2+5
            ));
    //new ghost that is 5 pixels away from the pacman.
    access.set_ghost_1(ghost_to_die);
    access.get_pacman().update_direction({0,1});
    //make the pacman move left


    ///
    /// CHECKS
    ///

    model.on_frame(dt); //make pacman eat power pellet

    CHECK( //ghost vulnerable
            access.get_ghost_1().is_vulnerable()
    );

    // Make a copy of the ghost for computing what we expect it to do.
    Ghost expected_ghost (model.get_pacman().get_position().right_by(
            model.get_pacman().get_dimensions().width/2+5
    ));
    expected_ghost.set_vulnerable(true);

    Pacman expected_pacman (model.get_pacman()); //I think this works?

    expected_ghost = expected_ghost.next(dt);
    expected_pacman = expected_pacman.next(dt); //move right

    // Local helper function (lambda) that runs both the expected characters
    // and the model for a frame and then checks that they agree.
    auto check_frame = [&] {
        CHECK(model.get_ghost1().operator==(expected_ghost));
        expected_ghost = expected_ghost.next(dt);
        expected_pacman = expected_pacman.next(dt);

        model.on_frame(dt);
    };

    // Simulate one frame in which the pacman hits the ghost,
    // which means that the ghost is reset.
    check_frame();
    expected_ghost.set_alive(false);

    CHECK( //ghost will respawn at the place it originally spawned
            expected_ghost.get_position() ==
            model.get_pacman().get_position().right_by(
                model.get_pacman().get_dimensions().width/2+1)
    );

    CHECK(
            expected_ghost.get_direction() == Dims<int>{0,-1}
    );

    //check 8 more frames.
    for(int i = 0; i < 8; i++) {
        check_frame();
    }

    // Now make a ghost and put it in front of the pacman.
    Ghost killer_ghost (model.get_pacman().get_position().right_by(
            model.get_pacman().get_dimensions().width/2+1
    ));
    model.set_ghost(1, killer_ghost);
    Ghost expected_ghost2 (model.get_pacman().get_position().right_by(
            model.get_pacman().get_dimensions().width/2+1
    ));

    // Simulate one frame in which the pacman hits the ghost,
    // which means that the pacman is reset.
    check_frame();
    expected_pacman = Pacman({352,322});

    CHECK(
            expected_ghost.operator==(access.get_ghost_1())
    );

    CHECK(
            expected_pacman.get_position() == model.get_pacman().get_position()
    );
    CHECK(
            expected_pacman.get_direction() == model.get_pacman().get_direction()
    );

}

//Test #2: round increments and maze changes when pacman eats all the
// pellets

TEST_CASE("Test #1: round increments + maze changes")
{

}

//Test #3: pacman cannot go through walls.

//Test #4: score increases when pacman eats a pellet, a power pellet, or a
// ghost.
TEST_CASE("Score increases when pacman eats a pellet, a power pellet, or a "
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
            model.get_pacman().get_dimensions().width/2+5
    ));
    //new ghost that is 5 pixels away from the pacman.
    access.set_ghost_1(ghost_to_die);
    access.get_pacman().update_direction({0,1});
    //make the pacman move left


    ///
    /// CHECKS
    ///

    model.on_frame(dt); //make pacman eat power pellet

    CHECK( //ghost vulnerable
            access.get_ghost_1().is_vulnerable()
    );
    CHECK( //ate power pellet --> raise score by 50
            access.get_score() == 50
    );

    model.on_frame(dt);

    // Simulate one frame in which the pacman hits the ghost,
    CHECK( //ate power pellet --> raise score by 50
            access.get_score() == 50
    );
    CHECK( //ghost eaten --> no longer vulnerable
            !access.get_ghost_1().is_vulnerable()
    );

}

//Test #5: Pacman loses lives and the game ends when pacman's lives = 0.
TEST_CASE("Pac-man Dies, Game over") {


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
