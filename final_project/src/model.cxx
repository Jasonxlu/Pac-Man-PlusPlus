#include "model.hxx"

Model::Model()
        : Model(24,16, 32)
{

}

Model::Model(int width, int height, int maze_size)
            : game_over_(false),
            m_({width, height}),
            maze_size_(maze_size),
            random_direction_source(0, 4)
{
    /// Set the outer border
    for (int x = 0; x < m_.dimensions().width; x++) {
        for (int y = 0; y < m_.dimensions().height; y++) {
            if (x == 0 || y == 0 ||
                x == m_.dimensions().width - 1
                || y == m_.dimensions().height - 1) {
                m_[{x,y}] = Tile::wall;
            }
        }
    }

    //Drawing Ghost Box
    for (int x = 0; x < m_.dimensions().width; x++) {
        for (int y = 0; y < m_.dimensions().height; y++) {

            if ((x==9 && y>5 && y<10) || (x==14 && y>5 && y<10) || (y==6
                                                                    && x>8 && x<15) || (y==9 && x>8 && x<15))
            {
                if(!(x>=11 && x<=12 && y==6))
                {
                    m_[{x,y}] = Tile::wall;
                }
            }
        }
    }

    maze_walls_ = m_.get_maze_walls();
}

/*
bool Model::character_hits_screen_wall(Character c) {
    return (c.get_position().x < screen_dims.width &&
        c.get_position().x > 0 &&
        c.get_position().y < screen_dims.height &&
        c.get_position().y > 0);
}
 */


bool Model::character_hits_maze_wall(Character c) {

    //this won't work because it's just looking at the center.
    /*
    //check if the tile at this character is a wall
    if(m_[screen_to_board_(c.get_position().into<int>())]
            == Tile::wall) {
        return true;
    }
    return false;
     */

    //loop thru all maze walls and ask if character is inside
    for(ge211::Posn<int> p: maze_walls_) {
        //check if c hits a wall that is positioned at p
        //and has width of 8 and height of 8 (hardcoded)
        if(c.hits_maze_wall(Block(
                board_to_screen(p).x,
                 board_to_screen(p).y,
                 30,30))) {
            return true;
        }
    }

    return false;
}

bool Model::pacman_overlaps_ghost(Pacman p, Ghost g)
{
    //if pacman hits ghost, call pacman hit_ghost(the ghost).
    //see if the result from that is true. If so, kill ghost.
    //If false, game over.
    if (p.overlaps_ghost(g)) {
        return true;
    }
    return false;
}

void Model::on_frame(double dt)
{

    if(game_over_) {
        return;
    }

    bool update_pacman = true;
    bool update_ghost_1 = true;
    bool update_ghost_2 = true;
    bool update_ghost_3 = true;
    bool update_ghost_4 = true;

    g1_.update_timer(dt);
    g2_.update_timer(dt);
    g3_.update_timer(dt);
    g4_.update_timer(dt);

    Ghost g1_next = g1_.next(dt);
    Ghost g2_next = g2_.next(dt);
    Ghost g3_next = g3_.next(dt);
    Ghost g4_next = g4_.next(dt);

    Pacman pacman_next = pacman_.next(dt);
    /*
    if(character_hits_screen_wall(pacman_next)) {
        //TODO: pacman hits screen wall --> set velocity to 0
        update_pacman = false; //don't update the pacman to its next position
    }
     */

    //Characters hitting walls!!!!!!!
    if(character_hits_maze_wall(pacman_next)) {
        //pacman hits maze wall --> set velocity to 0
        pacman_.set_velocity(0);
        update_pacman = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g1_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g1_.hit_wall(m_,
                     screen_to_board_(
                             g1_.get_position().into<int>()));
        //update_ghost_1 = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g2_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g2_.hit_wall(m_,
            screen_to_board_(
                    g2_.get_position().into<int>()));
        //update_ghost_2 = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g3_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g3_.hit_wall(m_,
                     screen_to_board_(
                             g3_.get_position().into<int>()));
        //update_ghost_3 = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g4_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g4_.hit_wall(m_,
                     screen_to_board_(
                             g4_.get_position().into<int>()));
        //update_ghost_4 = false; //don't update the pacman to its next position
    }



    /* BRENNAN COMMEMNT OUT FOR DEBUGGING
    //go through ghost nexts and ask if pacman hits it
    if(pacman_overlaps_ghost(pacman_next, g1_next)) {
        if(pacman_next.hit_ghost(g1_next)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g1_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_next, g2_next)) {
        if(pacman_next.hit_ghost(g2_next)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g2_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_next, g3_next)) {
        if(pacman_next.hit_ghost(g3_next)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g3_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_next, g4_next)) {
        if(pacman_next.hit_ghost(g4_next)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g4_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }
    */


    //TODO:check eat pellet
    // if(ball_next.destroy_brick(bricks)) {
    //     ball.reflect_vertical();
    //     ball.velocity.width+=random_boost_source.next();
    // }

    if(update_pacman) {
        pacman_ = pacman_.next(dt); //store the result in the pacman for real
    }

    if(update_ghost_1) {
        g1_ = g1_.next(dt);
    }
    if(update_ghost_2) {
        g2_ = g2_.next(dt);
    }
    if(update_ghost_3) {
        g3_ = g3_.next(dt);
    }
    if(update_ghost_4) {
        g4_ = g4_.next(dt);
    }
}

Maze
Model::maze_() const
{
    return m_;
}

ge211::Posn<int>
Model::screen_to_board_(ge211::Posn<int> pos) const
{
    return {pos.x / maze_size_, pos.y / maze_size_};
}

ge211::Posn<int>
Model::board_to_screen(ge211::Posn<int> pos) const
{
    return {maze_size_ * pos.x, maze_size_ * pos.y};
}