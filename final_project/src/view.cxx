#include "view.hxx"

static int const maze_size = 12*8; // Jason: Width x Height of the map? Not
// really sure just yet of what this constant does

View::View(Model const& model)
        : model_(model),
        //Jason Todo: These radii are just placeholders
        pacman(2, Color(255,255,0)),
        ghost1(2, Color(255,0,0)),
        ghost2(2, Color(0,255,0)),
        ghost3(2,Color(0,0,255)),
        ghost4(2,Color(150,150,150)),
        wall({maze_size/4,maze_size/4},Color(0,0,255))
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    //Jason: Just testing drawing sprites rn
    set.add_sprite(wall,{0,0},1);

}
