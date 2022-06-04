#include "view.hxx"

static int const maze_size = 32; // Jason: Proportions of the map


View::View(Model const& model)
        : model_(model),

        pacman("pacman_0.png"),
        wall("wall.png"),
        ghost1("red_ghost.png"),
        ghost2("blue_ghost.png"),
        ghost3("purple_ghost.png"),
        ghost4("green_ghost.png"),
        sans30{"sans.ttf", 20},
          sans30_massive{"sans.ttf", 70},
        pellet("pellet.png"),
        score("Score: ",sans30),
        lives("Lives: ",sans30),
        round("Round: ",sans30),
        game_over("GAME OVER", sans30_massive),
        ghostv("ghost_v.png"),
        ghost1nv("red_ghost.png"),
        ghost2nv("blue_ghost.png"),
        ghost3nv("purple_ghost.png"),
        ghost4nv("green_ghost.png"),
        pacman_ate("pacman_1.png"),
        pacman_orig("pacman_0.png")
{ }

void
View::draw(ge211::Sprite_set& set)
{

    if(model_.game_over()) {
        set.add_sprite(game_over,
                       {300,200}, 4);
    }

    //draw the score, life, and round counter
    std::string display_score ("Score: ");
    display_score.append(std::to_string(model_.get_score()));
    ge211::Text_sprite::Builder score_builder(sans30);
    score_builder.message(display_score);
    score.reconfigure(score_builder);

    set.add_sprite(score,
            {780,25}, 3);


    std::string display_lives ("Lives: ");
    display_lives.append(std::to_string(model_.get_pacman_lives()));
    ge211::Text_sprite::Builder lives_builder(sans30);
    lives_builder.message(display_lives);
    lives.reconfigure(lives_builder);

    set.add_sprite(lives,
            {780,75}, 3);

    std::string display_round ("Round: ");
    display_round.append(std::to_string(model_.get_round_number()));
    ge211::Text_sprite::Builder round_builder(sans30);
    round_builder.message(display_round);
    round.reconfigure(round_builder);

    set.add_sprite(round,
            {780,125}, 3);


    for(int i=0; i<24; i++) {
        for(int j=0; j<16; j++) {
            switch(model_.maze_()[{i,j}]) {
            case Tile::wall:
                set.add_sprite(wall,
                               {board_to_screen({i,j})},
                               1);
                break;
            case Tile::power_pellet:
                set.add_sprite(pellet,
                               {board_to_screen({i,j}).x + 8,
                                board_to_screen({i,j}).y +8},
                               1,
                               Transform::scale(3));
                break;
            case Tile::pellet:
                set.add_sprite(pellet,
                               {board_to_screen({i,j}).x + 16,
                                board_to_screen({i,j}).y +16},
                               1);
                break;
            case Tile::spawn_point:
                break;
            case Tile::path:
                break;
            }
        }
    }


    /// Drawing Characters

    if(model_.get_ghost1().is_vulnerable())
    {
        ghost1 = ghostv;
        ghost2 = ghostv;
        ghost3 = ghostv;
        ghost4 = ghostv;
    }
    else
    {
        ghost1 = ghost1nv;
        ghost2 = ghost2nv;
        ghost3 = ghost3nv;
        ghost4 = ghost4nv;
    }


    if(Model::get_ate())
    {
        pacman = pacman_ate;
    }
    else {
        pacman = pacman_orig;
    }


    //draw pacman
    set.add_sprite(pacman, {model_.get_pacman()
    .get_position().into<int>().x,model_.get_pacman().get_position().into<int>().y},
                   3,get_transform_pacman(model_.get_pacman().get_direction()));

    set.add_sprite(ghost1, {model_.get_ghost1().get_position().into<int>().x,
                            model_.get_ghost1().get_position().into<int>().y}
                    ,2, ge211::geometry::Transform::scale(1.4));

    set.add_sprite(ghost2, {model_.get_ghost2().get_position().into<int>().x
                            ,model_.get_ghost2().get_position().into<int>().y}
                    ,2, ge211::geometry::Transform::scale(1.4));

    set.add_sprite(ghost3, {model_.get_ghost3().get_position().into<int>().x
                            ,model_.get_ghost3().get_position().into<int>().y}
                    ,2, ge211::geometry::Transform::scale(1.4));

    set.add_sprite(ghost4, {model_.get_ghost4().get_position().into<int>().x
                            ,model_.get_ghost4().get_position().into<int>().y},
                   2, ge211::geometry::Transform::scale(1.4));

}

ge211::Transform
View::get_transform_pacman(Dimensions d) {
    if(d == ge211::Dims<int>({0,1})) {
        //pacman pointing down
       return ge211::geometry::Transform::scale(1.4)
                               .set_rotation(90);
    } else if(d == ge211::Dims<int>({0,-1})) {
        //pacman pointing up
        return ge211::geometry::Transform::scale(1.4)
                               .set_rotation(270).set_flip_v(true);
    } else if(d == ge211::Dims<int>({1,0})) {
        //pacman pointing right - this one is ok default
        return ge211::geometry::Transform::scale(1.4);
    } else {
        //pacman pointing left
        return ge211::geometry::Transform::scale(1.4)
                               .set_rotation(180).set_flip_v(true);
    }
}


View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:

    return {maze_size * model_.maze_().dimensions().width + 175, maze_size *
    model_.maze_().dimensions().height};
}

std::string
View::initial_window_title() const
{
    return "Pac-Man++";
}

View::Position
View::board_to_screen(ge211::Posn<int> pos) const
{
    return {maze_size * pos.x, maze_size * pos.y};
}

ge211::Posn<int>
View::screen_to_board(View::Position pos) const
{
    return {pos.x / maze_size, pos.y / maze_size};
}
