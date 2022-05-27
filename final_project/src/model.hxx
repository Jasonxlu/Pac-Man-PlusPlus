#pragma once

#include <ge211.hxx>

#include "board.hxx"


class Model
{
public:

    ///
    /// CONSTRUCTOR
    ///

    // Constructs a model from a game configuration.
    //
    // The `= Game_config()` syntax makes the argument optional, in which case
    // it defaults to the default `Game_config`. That is, you can explicitly
    // create a `Game_config` to pass the `Model` constructor like so:
    //
    //     Game_config config;
    //     config.ball_radius = 2;
    //     Model model(config);
    //
    // Or you can omit the constructor argument, in which case you get
    // the default `Game_config` (as defined in game_config.cpp):
    //
    //     Model model;
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby C++ would automatically convert
    // `Game_config`s into `Model`s if needed. You don't want that.
    explicit Model(Game_config const& config = Game_config());

    /// Returns whether the game is finished. This is true when neither
    /// player can move.
    bool is_game_over() const
    { return; } //TODO

    /// Returns whether the round is finished. This is true when the pacman
    /// gets eaten but still has >= 1 lives.
    bool is_round_over() const
    { return; } //TODO


    void on_frame(double dt);


    ///
    /// MEMBER VARIABLES
    ///

    // The configuration parameters of the model. See game_config.hxx for a
    // description of what this determines. Models can be constructed with
    // different configurations, but the configuration never changes on an
    // existing model.
    Game_config const config;

    //characters

};
