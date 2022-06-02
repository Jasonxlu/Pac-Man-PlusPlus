#include "view.hxx"

static int const maze_size = 32; // Jason: Proportions of the map

View::View(Model const& model)
        : model_(model),
        //Jason Todo: These radii are just placeholders
        pacman(10, Color(255,255,0)),
        ghost1(10, Color(255,0,0)),
        ghost2(10, Color(0,255,0)),
        ghost3(10,Color(25,240,130)),
        ghost4(10,Color(100,15,175)),
        wall({maze_size-1,maze_size-1},Color(0,0,255))
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    //Jason: Just testing drawing sprites rn

    /// Drawing the outer border
    for (int x = 0; x < model_.maze_().dimensions().width; x++) {
        for (int y = 0; y < model_.maze_().dimensions().height; y++) {
            if (x == 0 || y == 0 ||
                x == model_.maze_().dimensions().width - 1
                || y == model_.maze_().dimensions().height - 1) {
                set.add_sprite(wall,
                               {board_to_screen({x, y}).x,
                                board_to_screen({x,y}).y},
                               1);
            }
        }
    }

    //Drawing Ghost Box
    for (int x = 0; x < model_.maze_().dimensions().width; x++) {
        for (int y = 0; y < model_.maze_().dimensions().height; y++) {

            if ((x==9 && y>5 && y<10) || (x==14 && y>5 && y<10) || (y==6
            && x>8 && x<15) || (y==9 && x>8 && x<15))
            {
                if(!(x>=11 && x<=12 && y==6))
                {
                    set.add_sprite(wall,
                                   {board_to_screen({x, y}).x,
                                    board_to_screen({x, y}).y},
                                   1);
                }
            }
        }
    }

    /// Drawing Characters
    set.add_sprite(pacman, model_.get_pacman().get_position().into<int>(),
                    1);
    set.add_sprite(ghost1, model_.get_ghost1().get_position().into<int>(),
                   2);
    set.add_sprite(ghost2, model_.get_ghost2().get_position().into<int>(),
                   2);
    set.add_sprite(ghost3, model_.get_ghost3().get_position().into<int>(),
                   2);
    set.add_sprite(ghost4, model_.get_ghost4().get_position().into<int>(),
                   2);

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
