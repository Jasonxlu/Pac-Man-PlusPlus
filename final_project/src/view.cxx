#include "view.hxx"

static int const maze_size = 12*8; // Jason: Proportions of the map

View::View(Model const& model)
        : model_(model),
        //Jason Todo: These radii are just placeholders
        pacman(10, Color(255,255,0)),
        ghost1(10, Color(255,0,0)),
        ghost2(10, Color(0,255,0)),
        ghost3(10,Color(25,240,130)),
        ghost4(10,Color(100,15,175)),
        wall({maze_size/4-1,maze_size/4-1},Color(0,0,255))
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    //Jason: Just testing drawing sprites rn

    /// Drawing the outer border
    for (int x = 0; x < model_.maze_().dimensions().width * 4; x++) {
        for (int y = 0; y < model_.maze_().dimensions().height * 4; y++) {
            if (x == 0 || y == 0 ||
                x == model_.maze_().dimensions().width * 4 - 1
                || y == model_.maze_().dimensions().height * 4 - 1) {
                set.add_sprite(wall,
                               {board_to_screen({x, y}).x,
                                board_to_screen({x,y}).y},
                               1);
            }
        }
    }

    //Drawing Ghost Box
    for (int x = 0; x < model_.maze_().dimensions().width * 4; x++) {
        for (int y = 0; y < model_.maze_().dimensions().height * 4; y++) {
            if ((x==20 && y>13 && y <19) || (x==28 && y>13 && y <19) || (y==14
            && x>19 && x<29) || (y==18 && x>19 && x<29))
            {
                if(!(x>=23 && x<=25 && y==14))
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
    set.add_sprite(pacman, board_to_screen({24, 13}), 1);
    set.add_sprite(ghost1, board_to_screen({8, 4}), 1);
    set.add_sprite(ghost2, board_to_screen({5, 7}), 1);
    set.add_sprite(ghost3, board_to_screen({2, 7}), 1);
    set.add_sprite(ghost4, board_to_screen({7, 7}), 1);

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
    return {maze_size * pos.x / 4, maze_size * pos.y / 4};
}

ge211::Posn<int>
View::screen_to_board(View::Position pos) const
{
    return {pos.x / maze_size, pos.y / maze_size};
}
