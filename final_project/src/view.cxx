#include "view.hxx"

static int const maze_size = 12*8; // Jason: Width x Height of the map? Not
// really sure just yet of what this constant does

View::View(Model const& model)
        : model_(model),
        //Jason Todo: These radii are just placeholders
        pacman(10, Color(255,255,0)),
        ghost1(2, Color(255,0,0)),
        ghost2(2, Color(0,255,0)),
        ghost3(2,Color(0,0,255)),
        ghost4(2,Color(150,150,150)),
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
                               {board_to_screen({x, y}).x / 4,
                                board_to_screen({x,y}).y /4},
                               1);
            }
        }
    }
    /// Drawing Characters
    set.add_sprite(pacman, board_to_screen({5, 5}), 1);

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
