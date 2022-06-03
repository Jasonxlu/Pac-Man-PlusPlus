#include "model.hxx"

Model::Model()
        : Model(24,16, 32)
{}

Model::Model(int width, int height, int maze_size)
            : game_over_(false),
            m_({width, height}),
            pacman_({352,320}),
            g1_({352,224}),
            g2_({352,256}),
            g3_({384,224}),
            g4_({384,256}),
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

            if ((x==10 && y>5 && y<10) || (x==13 && y>5 && y<10) ||
            (y==6 && x>9 && x<14) || (y==9 && x>9 && x<14))
            {
                if(!(x>=11 && x<=12 && y==6))
                {
                    m_[{x,y}] = Tile::wall;
                }
            }
        }
    }

    //Drawing Map 1
    m_[{10,1}] = Tile::wall;
    m_[{11,1}] = Tile::wall;
    m_[{12,1}] = Tile::wall;
    m_[{13,1}] = Tile::wall;

    m_[{2,2}] = Tile::wall;
    m_[{3,2}] = Tile::wall;
    m_[{4,2}] = Tile::wall;
    m_[{5,2}] = Tile::wall;
    m_[{6,2}] = Tile::wall;
    m_[{8,2}] = Tile::wall;
    m_[{10,2}] = Tile::wall;
    m_[{11,2}] = Tile::wall;
    m_[{12,2}] = Tile::wall;
    m_[{13,2}] = Tile::wall;
    m_[{15,2}] = Tile::wall;
    m_[{17,2}] = Tile::wall;
    m_[{18,2}] = Tile::wall;
    m_[{19,2}] = Tile::wall;
    m_[{20,2}] = Tile::wall;
    m_[{21,2}] = Tile::wall;

    m_[{2,3}] = Tile::wall;
    m_[{3,3}] = Tile::wall;
    m_[{4,3}] = Tile::wall;
    m_[{5,3}] = Tile::wall;
    m_[{6,3}] = Tile::wall;
    m_[{8,3}] = Tile::wall;
    m_[{15,3}] = Tile::wall;
    m_[{17,3}] = Tile::wall;
    m_[{18,3}] = Tile::wall;
    m_[{19,3}] = Tile::wall;
    m_[{20,3}] = Tile::wall;
    m_[{21,3}] = Tile::wall;

    m_[{8,4}] = Tile::wall;
    m_[{10,4}] = Tile::wall;
    m_[{11,4}] = Tile::wall;
    m_[{12,4}] = Tile::wall;
    m_[{13,4}] = Tile::wall;
    m_[{15,4}] = Tile::wall;

    m_[{1,5}] = Tile::wall;
    m_[{2,5}] = Tile::wall;
    m_[{4,5}] = Tile::wall;
    m_[{6,5}] = Tile::wall;
    m_[{8,5}] = Tile::wall;
    m_[{15,5}] = Tile::wall;
    m_[{17,5}] = Tile::wall;
    m_[{19,5}] = Tile::wall;
    m_[{21,5}] = Tile::wall;
    m_[{22,5}] = Tile::wall;

    m_[{10,6}] = Tile::wall;
    m_[{13,6}] = Tile::wall;
    m_[{4,6}] = Tile::wall;
    m_[{6,6}] = Tile::wall;
    m_[{8,6}] = Tile::wall;
    m_[{15,6}] = Tile::wall;
    m_[{17,6}] = Tile::wall;
    m_[{19,6}] = Tile::wall;

    m_[{1,7}] = Tile::wall;
    m_[{2,7}] = Tile::wall;
    m_[{4,7}] = Tile::wall;
    m_[{10,7}] = Tile::wall;
    m_[{13,7}] = Tile::wall;
    m_[{19,7}] = Tile::wall;
    m_[{21,7}] = Tile::wall;
    m_[{22,7}] = Tile::wall;

    m_[{1,8}] = Tile::wall;
    m_[{2,8}] = Tile::wall;
    m_[{4,8}] = Tile::wall;
    m_[{6,8}] = Tile::wall;
    m_[{7,8}] = Tile::wall;
    m_[{8,8}] = Tile::wall;
    m_[{9,8}] = Tile::wall;
    m_[{14,8}] = Tile::wall;
    m_[{15,8}] = Tile::wall;
    m_[{16,8}] = Tile::wall;
    m_[{17,8}] = Tile::wall;
    m_[{19,8}] = Tile::wall;
    m_[{21,8}] = Tile::wall;
    m_[{22,8}] = Tile::wall;

    m_[{1,9}] = Tile::wall;
    m_[{2,9}] = Tile::wall;
    m_[{4,9}] = Tile::wall;
    m_[{19,9}] = Tile::wall;
    m_[{21,9}] = Tile::wall;
    m_[{22,9}] = Tile::wall;

    m_[{4,10}] = Tile::wall;
    m_[{6,10}] = Tile::wall;
    m_[{7,10}] = Tile::wall;
    m_[{8,10}] = Tile::wall;
    m_[{15,10}] = Tile::wall;
    m_[{16,10}] = Tile::wall;
    m_[{17,10}] = Tile::wall;
    m_[{19,10}] = Tile::wall;

    m_[{2,11}] = Tile::wall;
    m_[{3,11}] = Tile::wall;
    m_[{4,11}] = Tile::wall;
    m_[{6,11}] = Tile::wall;
    m_[{7,11}] = Tile::wall;
    m_[{8,11}] = Tile::wall;
    m_[{10,11}] = Tile::wall;
    m_[{11,11}] = Tile::wall;
    m_[{12,11}] = Tile::wall;
    m_[{13,11}] = Tile::wall;
    m_[{15,11}] = Tile::wall;
    m_[{16,11}] = Tile::wall;
    m_[{17,11}] = Tile::wall;
    m_[{19,11}] = Tile::wall;
    m_[{20,11}] = Tile::wall;
    m_[{21,11}] = Tile::wall;

    m_[{10,12}] = Tile::wall;
    m_[{11,12}] = Tile::wall;
    m_[{12,12}] = Tile::wall;
    m_[{13,12}] = Tile::wall;

    m_[{10,13}] = Tile::wall;
    m_[{11,13}] = Tile::wall;
    m_[{12,13}] = Tile::wall;
    m_[{13,13}] = Tile::wall;
    m_[{1,13}] = Tile::wall;
    m_[{2,13}] = Tile::wall;
    m_[{4,13}] = Tile::wall;
    m_[{5,13}] = Tile::wall;
    m_[{6,13}] = Tile::wall;
    m_[{8,13}] = Tile::wall;
    m_[{15,13}] = Tile::wall;
    m_[{17,13}] = Tile::wall;
    m_[{18,13}] = Tile::wall;
    m_[{19,13}] = Tile::wall;
    m_[{21,13}] = Tile::wall;
    m_[{22,13}] = Tile::wall;

    m_[{8,14}] = Tile::wall;
    m_[{15,14}] = Tile::wall;









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
                 32,32))) {
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

    g1_.update_timer(dt);
    g2_.update_timer(dt);
    g3_.update_timer(dt);
    g4_.update_timer(dt);

    Ghost g1_next = g1_.next(dt);
    Ghost g2_next = g2_.next(dt);
    Ghost g3_next = g3_.next(dt);
    Ghost g4_next = g4_.next(dt);

    Pacman pacman_next = pacman_.next(dt);

    //Characters hitting walls!!!!!!!
    if(character_hits_maze_wall(pacman_next)) {
        //pacman hits maze wall --> set velocity to 0
        pacman_.set_velocity(0);
        update_pacman = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g1_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g1_.hit_wall(m_, random_direction_source.next() ,
                     screen_to_board_(
                             g1_.get_position().into<int>()));
        //update_ghost_1 = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g2_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g2_.hit_wall(m_, random_direction_source.next(),
            screen_to_board_(
                    g2_.get_position().into<int>()));
        //update_ghost_2 = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g3_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g3_.hit_wall(m_, random_direction_source.next(),
                     screen_to_board_(
                             g3_.get_position().into<int>()));
        //update_ghost_3 = false; //don't update the pacman to its next position
    }
    if(character_hits_maze_wall(g4_next)) {
        //ghost hits maze wall --> call ghost hit_wall(Maze)
        g4_.hit_wall(m_, random_direction_source.next(),
                     screen_to_board_(
                             g4_.get_position().into<int>()));
        //update_ghost_4 = false; //don't update the pacman to its next position
    }



    //TODO: CHANGE
    //go through ghost nexts and ask if pacman hits it
    if(pacman_overlaps_ghost(pacman_, g1_)) {
        //if the pacman does hit the ghost, ask what happens when it does.
        if(pacman_.hit_ghost(g1_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g1_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_, g2_)) {
        if(pacman_.hit_ghost(g2_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g2_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_, g3_)) {
        if(pacman_.hit_ghost(g3_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g3_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_, g4_)) {
        if(pacman_.hit_ghost(g4_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g4_.set_alive(false);
        } else {
            game_over_ = true;
            return; //return immediately if game over - don't update anything
        }
    }


    //TODO:check eat pellet
    // if(ball_next.destroy_brick(bricks)) {
    //     ball.reflect_vertical();
    //     ball.velocity.width+=random_boost_source.next();
    // }

    //printf("update_pacman: %d", update_pacman);
    if(update_pacman) {
        pacman_ = pacman_.next(dt); //store the result in the pacman for real
    }

    g1_ = g1_.next(dt);
    g2_ = g2_.next(dt);
    g3_ = g3_.next(dt);
    g4_ = g4_.next(dt);
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


void
Model::update_pacman_direction(Dimensions d) {
    pacman_.update_direction(d);
}
