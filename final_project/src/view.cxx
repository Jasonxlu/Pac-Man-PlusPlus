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
        ghost4("green_ghost.png")


{ }

void
View::draw(ge211::Sprite_set& set)
{

    //draw the walls
    for(Position p : model_.maze_().get_maze_walls()) {
        set.add_sprite(wall,
                       {board_to_screen(p)},
                       1);
    }

    /// Drawing Characters
    set.add_sprite(pacman, {model_.get_pacman().get_position().into<int>().x,
            model_.get_pacman().get_position().into<int>().y},
                    3, ge211::geometry::Transform::scale(1.4));

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
View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return maze_size * model_.maze_().dimensions();
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
