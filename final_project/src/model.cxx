#include "model.hxx"


Model::Model() :
    game_over_(false)
{

}


bool Model::character_hits_screen_wall(Character c) {
    return (c.get_position().x < screen_dims.width &&
        c.get_position().x > 0 &&
        c.get_position().y < screen_dims.height &&
        c.get_position().y > 0);
}

bool Model::character_hits_maze_wall(Character c) {
    //loop thru all maze walls and ask if character is inside
    for(Block r : m.walls) {
        if(c.hits_maze_wall(r)) {
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
    if(p.overlaps_ghost(g)) {
        return p.hit_ghost(g);
    }
}

void Model::on_frame(double dt)
{
    if(game_over_) {
        return;
    }

    Pacman pacman_next = pacman_.next(dt);
    if(character_hits_screen_wall(pacman_next)) {
        //TODO: pacman hits screen wall --> set velocity to 0
        return; //don't update the ball to its next position
    }

    if(character_hits_maze_wall(pacman_next)) {
        //pacman hits maze wall --> set velocity to 0
        return; //don't update the ball to its next position
    }

    if(pacman_overlaps_ghost(pacman_next, g1_)) {
        //TODO: replace with ghost_next
        g1_.set_alive(false);
    } else {
        game_over_ = true;
    }

    if(ball_next.destroy_brick(bricks)) {
        ball.reflect_vertical();
        ball.velocity.width+=random_boost_source.next();
    }
    pacman_ = pacman_.next(dt); //store the result in the ball for real
}