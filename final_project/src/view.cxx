#include "view.hxx"

static int const maze_size = 32; // Jason: Proportions of the map


View::View(Model const& model)
        : model_(model),
        //Jason Todo: These radii are just placeholders

        pacman("pacman_open.png"),
        wall("wall.png"),
        ghost1("red_ghost.png"),
        ghost2("blue_ghost.png"),
        ghost3("purple_ghost.png"),
        ghost4("green_ghost.png"),
        sans30{"sans.ttf", 20},
        pellet("pellet.png"),
        score("Score: 0",sans30),
        lives("Lives: 3",sans30),
        round("Round: 1",sans30)
{ }

void
View::draw(ge211::Sprite_set& set)
{

    //draw the score, life, and round counter
    set.add_sprite(score, {800,25}, 3);
    set.add_sprite(lives, {800,100}, 3);
    set.add_sprite(round, {800,175}, 3);

    //draw the walls
    for(Position p : model_.maze_().get_maze_walls()) {
        set.add_sprite(wall,
                       {board_to_screen(p)},
                       1);
    }

    //draw the pellets
    for(Position p : model_.maze_().get_maze_pellets()) {
        set.add_sprite(pellet,
                       {board_to_screen(p).x + 16, board_to_screen(p).y +16},
                       1);
    }

    /// Drawing Characters

    //draw pacman
    set.add_sprite(pacman, {model_.get_pacman().get_position().into<int>().x,
                            model_.get_pacman().get_position().into<int>().y},
                   3,
                   get_transform_pacman(model_.get_pacman().get_direction()));


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

    return {maze_size * model_.maze_().dimensions().width + 150, maze_size *
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
