#include "model.hxx"

Model::Model(int width, int height, int maze_size)
            : game_over_(false),
            m_({width, height}),
            pacman_({352,322}),
            g1_({352,224}),
            g2_({352,256}),
            g3_({384,224}),
            g4_({384,256}),
            maze_size_(maze_size),
            random_direction_source(0, 4)
{
    Maze m2_ = Maze({width,height});
    Maze m3_ = Maze({width,height});

    /// Set the outer border
    for (int x = 0; x < m_.dimensions().width; x++) {
        for (int y = 0; y < m_.dimensions().height; y++) {
            if (x == 0 || y == 0 ||
                x == m_.dimensions().width - 1
                || y == m_.dimensions().height - 1) {
                m_[{x,y}] = Tile::wall;
                m2_[{x,y}] = Tile::wall;
                m3_[{x,y}] = Tile::wall;
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
                    m2_[{x,y}] = Tile::wall;
                    m3_[{x,y}] = Tile::wall;
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

    //set power pellets
    m_[{3,10}] = Tile::power_pellet;
    m_[{6,4}] = Tile::power_pellet;
    m_[{17,4}] = Tile::power_pellet;
    m_[{20,10}] = Tile::power_pellet;

    //set spawn points
    m_[{11,7}] = Tile::spawn_point;
    m_[{12,7}] = Tile::spawn_point;
    m_[{11,8}] = Tile::spawn_point;
    m_[{12,8}] = Tile::spawn_point;
    m_[{11,10}] = Tile::spawn_point;



    m_.set_pellets();

    // Maze 2
    m2_[{10,1}] = Tile::wall;
    m2_[{11,1}] = Tile::wall;
    m2_[{12,1}] = Tile::wall;
    m2_[{13,1}] = Tile::wall;

    m2_[{2,2}] = Tile::wall;
    m2_[{3,2}] = Tile::wall;
    m2_[{4,2}] = Tile::wall;
    m2_[{6,2}] = Tile::wall;
    m2_[{8,2}] = Tile::wall;
    m2_[{15,2}] = Tile::wall;
    m2_[{17,2}] = Tile::wall;
    m2_[{19,2}] = Tile::wall;
    m2_[{20,2}] = Tile::wall;
    m2_[{21,2}] = Tile::wall;

    m2_[{2,3}] = Tile::wall;
    m2_[{3,3}] = Tile::wall;
    m2_[{4,3}] = Tile::wall;
    m2_[{6,3}] = Tile::wall;
    m2_[{8,3}] = Tile::wall;
    m2_[{15,3}] = Tile::wall;
    m2_[{17,3}] = Tile::wall;
    m2_[{19,3}] = Tile::wall;
    m2_[{20,3}] = Tile::wall;
    m2_[{21,3}] = Tile::wall;
    m2_[{10,3}] = Tile::wall;
    m2_[{11,3}] = Tile::wall;
    m2_[{12,3}] = Tile::wall;
    m2_[{13,3}] = Tile::wall;

    m2_[{2,4}] = Tile::wall;
    m2_[{3,4}] = Tile::wall;
    m2_[{4,4}] = Tile::wall;
    m2_[{6,4}] = Tile::wall;
    m2_[{8,4}] = Tile::wall;
    m2_[{15,4}] = Tile::wall;
    m2_[{17,4}] = Tile::wall;
    m2_[{19,4}] = Tile::wall;
    m2_[{20,4}] = Tile::wall;
    m2_[{21,4}] = Tile::wall;
    m2_[{10,4}] = Tile::wall;
    m2_[{11,4}] = Tile::wall;
    m2_[{12,4}] = Tile::wall;
    m2_[{13,4}] = Tile::wall;

    m2_[{6,5}] = Tile::wall;
    m2_[{8,5}] = Tile::wall;
    m2_[{15,5}] = Tile::wall;
    m2_[{17,5}] = Tile::wall;

    m2_[{2,6}] = Tile::wall;
    m2_[{3,6}] = Tile::wall;
    m2_[{4,6}] = Tile::wall;
    m2_[{5,6}] = Tile::wall;
    m2_[{6,6}] = Tile::wall;
    m2_[{8,6}] = Tile::wall;
    m2_[{15,6}] = Tile::wall;
    m2_[{17,6}] = Tile::wall;
    m2_[{18,6}] = Tile::wall;
    m2_[{19,6}] = Tile::wall;
    m2_[{20,6}] = Tile::wall;
    m2_[{21,6}] = Tile::wall;

    m2_[{6,7}] = Tile::wall;
    m2_[{8,7}] = Tile::wall;
    m2_[{15,7}] = Tile::wall;
    m2_[{17,7}] = Tile::wall;

    m2_[{2,8}] = Tile::wall;
    m2_[{4,8}] = Tile::wall;
    m2_[{6,8}] = Tile::wall;
    m2_[{8,8}] = Tile::wall;
    m2_[{15,8}] = Tile::wall;
    m2_[{17,8}] = Tile::wall;
    m2_[{19,8}] = Tile::wall;
    m2_[{21,8}] = Tile::wall;

    m2_[{2,9}] = Tile::wall;
    m2_[{4,9}] = Tile::wall;
    m2_[{6,9}] = Tile::wall;
    m2_[{8,9}] = Tile::wall;
    m2_[{15,9}] = Tile::wall;
    m2_[{17,9}] = Tile::wall;
    m2_[{19,9}] = Tile::wall;
    m2_[{21,9}] = Tile::wall;

    m2_[{2,10}] = Tile::wall;
    m2_[{4,10}] = Tile::wall;
    m2_[{19,10}] = Tile::wall;
    m2_[{21,10}] = Tile::wall;

    m2_[{2,11}] = Tile::wall;
    m2_[{4,11}] = Tile::wall;
    m2_[{6,11}] = Tile::wall;
    m2_[{7,11}] = Tile::wall;
    m2_[{8,11}] = Tile::wall;
    m2_[{9,11}] = Tile::wall;
    m2_[{10,11}] = Tile::wall;
    m2_[{11,11}] = Tile::wall;
    m2_[{12,11}] = Tile::wall;
    m2_[{13,11}] = Tile::wall;
    m2_[{14,11}] = Tile::wall;
    m2_[{15,11}] = Tile::wall;
    m2_[{16,11}] = Tile::wall;
    m2_[{17,11}] = Tile::wall;
    m2_[{19,11}] = Tile::wall;
    m2_[{21,11}] = Tile::wall;

    m2_[{10,12}] = Tile::wall;
    m2_[{11,12}] = Tile::wall;
    m2_[{12,12}] = Tile::wall;
    m2_[{13,12}] = Tile::wall;

    m2_[{2,13}] = Tile::wall;
    m2_[{3,13}] = Tile::wall;
    m2_[{4,13}] = Tile::wall;
    m2_[{5,13}] = Tile::wall;
    m2_[{6,13}] = Tile::wall;
    m2_[{7,13}] = Tile::wall;
    m2_[{8,13}] = Tile::wall;
    m2_[{10,13}] = Tile::wall;
    m2_[{11,13}] = Tile::wall;
    m2_[{12,13}] = Tile::wall;
    m2_[{13,13}] = Tile::wall;
    m2_[{15,13}] = Tile::wall;
    m2_[{16,13}] = Tile::wall;
    m2_[{17,13}] = Tile::wall;
    m2_[{18,13}] = Tile::wall;
    m2_[{19,13}] = Tile::wall;
    m2_[{20,13}] = Tile::wall;
    m2_[{21,13}] = Tile::wall;

    //set power pellets and spawn points
    m2_[{5,5}] = Tile::power_pellet;
    m2_[{9,12}] = Tile::power_pellet;
    m2_[{18,5}] = Tile::power_pellet;
    m2_[{14,12}] = Tile::power_pellet;

    m2_[{11,10}] = Tile::spawn_point;
    m2_[{11,7}] = Tile::spawn_point;
    m2_[{12,7}] = Tile::spawn_point;
    m2_[{11,8}] = Tile::spawn_point;
    m2_[{12,8}] = Tile::spawn_point;

    m2_.set_pellets();

    m3_[{2,2}] = Tile::wall;
    m3_[{3,2}] = Tile::wall;
    m3_[{5,2}] = Tile::wall;
    m3_[{7,2}] = Tile::wall;
    m3_[{8,2}] = Tile::wall;
    m3_[{9,2}] = Tile::wall;
    m3_[{11,2}] = Tile::wall;
    m3_[{12,2}] = Tile::wall;
    m3_[{14,2}] = Tile::wall;
    m3_[{15,2}] = Tile::wall;
    m3_[{16,2}] = Tile::wall;
    m3_[{18,2}] = Tile::wall;
    m3_[{20,2}] = Tile::wall;
    m3_[{21,2}] = Tile::wall;

    m3_[{2,3}] = Tile::wall;
    m3_[{3,3}] = Tile::wall;
    m3_[{5,3}] = Tile::wall;
    m3_[{11,3}] = Tile::wall;
    m3_[{12,3}] = Tile::wall;
    m3_[{18,3}] = Tile::wall;
    m3_[{20,3}] = Tile::wall;
    m3_[{21,3}] = Tile::wall;

    m3_[{2,4}] = Tile::wall;
    m3_[{3,4}] = Tile::wall;
    m3_[{5,4}] = Tile::wall;
    m3_[{7,4}] = Tile::wall;
    m3_[{8,4}] = Tile::wall;
    m3_[{10,4}] = Tile::wall;
    m3_[{11,4}] = Tile::wall;
    m3_[{12,4}] = Tile::wall;
    m3_[{13,4}] = Tile::wall;
    m3_[{15,4}] = Tile::wall;
    m3_[{16,4}] = Tile::wall;
    m3_[{18,4}] = Tile::wall;
    m3_[{20,4}] = Tile::wall;
    m3_[{21,4}] = Tile::wall;

    m3_[{5,5}] = Tile::wall;
    m3_[{7,5}] = Tile::wall;
    m3_[{8,5}] = Tile::wall;
    m3_[{15,5}] = Tile::wall;
    m3_[{16,5}] = Tile::wall;
    m3_[{18,5}] = Tile::wall;

    m3_[{1,6}] = Tile::wall;
    m3_[{2,6}] = Tile::wall;
    m3_[{4,6}] = Tile::wall;
    m3_[{5,6}] = Tile::wall;
    m3_[{7,6}] = Tile::wall;
    m3_[{8,6}] = Tile::wall;
    m3_[{15,6}] = Tile::wall;
    m3_[{16,6}] = Tile::wall;
    m3_[{18,6}] = Tile::wall;
    m3_[{19,6}] = Tile::wall;
    m3_[{21,6}] = Tile::wall;
    m3_[{22,6}] = Tile::wall;

    m3_[{1,7}] = Tile::wall;
    m3_[{2,7}] = Tile::wall;
    m3_[{4,7}] = Tile::wall;
    m3_[{5,7}] = Tile::wall;
    m3_[{7,7}] = Tile::wall;
    m3_[{8,7}] = Tile::wall;
    m3_[{15,7}] = Tile::wall;
    m3_[{16,7}] = Tile::wall;
    m3_[{18,7}] = Tile::wall;
    m3_[{19,7}] = Tile::wall;
    m3_[{21,7}] = Tile::wall;
    m3_[{22,7}] = Tile::wall;

    m3_[{5,8}] = Tile::wall;
    m3_[{7,8}] = Tile::wall;
    m3_[{8,8}] = Tile::wall;
    m3_[{15,8}] = Tile::wall;
    m3_[{16,8}] = Tile::wall;
    m3_[{18,8}] = Tile::wall;

    m3_[{2,9}] = Tile::wall;
    m3_[{3,9}] = Tile::wall;
    m3_[{5,9}] = Tile::wall;
    m3_[{7,9}] = Tile::wall;
    m3_[{8,9}] = Tile::wall;
    m3_[{15,9}] = Tile::wall;
    m3_[{16,9}] = Tile::wall;
    m3_[{18,9}] = Tile::wall;
    m3_[{20,9}] = Tile::wall;
    m3_[{21,9}] = Tile::wall;

    m3_[{2,10}] = Tile::wall;
    m3_[{3,10}] = Tile::wall;
    m3_[{5,10}] = Tile::wall;
    m3_[{18,10}] = Tile::wall;
    m3_[{20,10}] = Tile::wall;
    m3_[{21,10}] = Tile::wall;

    m3_[{2,11}] = Tile::wall;
    m3_[{3,11}] = Tile::wall;
    m3_[{5,11}] = Tile::wall;
    m3_[{7,11}] = Tile::wall;
    m3_[{8,11}] = Tile::wall;
    m3_[{9,11}] = Tile::wall;
    m3_[{10,11}] = Tile::wall;
    m3_[{11,11}] = Tile::wall;
    m3_[{12,11}] = Tile::wall;
    m3_[{13,11}] = Tile::wall;
    m3_[{14,11}] = Tile::wall;
    m3_[{15,11}] = Tile::wall;
    m3_[{16,11}] = Tile::wall;
    m3_[{18,11}] = Tile::wall;
    m3_[{20,11}] = Tile::wall;
    m3_[{21,11}] = Tile::wall;

    m3_[{2,12}] = Tile::wall;
    m3_[{21,12}] = Tile::wall;

    m3_[{2,13}] = Tile::wall;
    m3_[{4,13}] = Tile::wall;
    m3_[{5,13}] = Tile::wall;
    m3_[{6,13}] = Tile::wall;
    m3_[{7,13}] = Tile::wall;
    m3_[{8,13}] = Tile::wall;
    m3_[{9,13}] = Tile::wall;
    m3_[{10,13}] = Tile::wall;
    m3_[{11,13}] = Tile::wall;
    m3_[{12,13}] = Tile::wall;
    m3_[{13,13}] = Tile::wall;
    m3_[{14,13}] = Tile::wall;
    m3_[{15,13}] = Tile::wall;
    m3_[{16,13}] = Tile::wall;
    m3_[{17,13}] = Tile::wall;
    m3_[{18,13}] = Tile::wall;
    m3_[{19,13}] = Tile::wall;
    m3_[{21,13}] = Tile::wall;



    //set power pellets and spawn points
    m3_[{1,5}] = Tile::power_pellet;
    m3_[{3,12}] = Tile::power_pellet;
    m3_[{22,5}] = Tile::power_pellet;
    m3_[{20,12}] = Tile::power_pellet;

    m3_[{11,10}] = Tile::spawn_point;
    m3_[{11,7}] = Tile::spawn_point;
    m3_[{12,7}] = Tile::spawn_point;
    m3_[{11,8}] = Tile::spawn_point;
    m3_[{12,8}] = Tile::spawn_point;
    m3_.set_pellets();

    mazes_.push_back(m_);
    mazes_.push_back(m2_);
    mazes_.push_back(m3_);

    maze_walls_ = m_.get_maze_walls();

    set_level(round_num);
    reset_maze_change();

}

bool Model::character_hits_maze_wall(Character c) {


    //loop through all maze walls and ask if character is inside
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

bool Model::pacman_overlaps_pellet() {
    Posn<int> pacman_board_pos =
            screen_to_board_(pacman_.get_position().into<int>());
    if(m_[pacman_board_pos]
       == Tile::pellet) {
        //pacman eat regular pellet
        m_.destroy_pellet(pacman_board_pos);
        increment_score(pellet_score_); //add pellet score to score
        ate = true;
        return true;
    } else if(m_[pacman_board_pos] == Tile::power_pellet) {
        //pacman eat power pellet
        m_.destroy_pellet(pacman_board_pos);
        increment_score(power_pellet_score_); //add power pellet score to score
        g1_.set_vulnerable(true);
        g2_.set_vulnerable(true);
        g3_.set_vulnerable(true);
        g4_.set_vulnerable(true);
        //set ghosts to vulnerable
        ate = true;
        return true;
    }
    ate = false;
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

void Model::increment_score(int i) {
    score_ += i;
}

void Model::increment_round() {
    round_number_++;
    m_ = mazes_[round_number_%3]; //change maze
    reset_maze_change();
}

void Model::decrement_pacman_lives() {
    pacman_lives_--;
    if(pacman_lives_ <= 0) { //game over
        game_over_ = true;
        return;
    }

    //reset pacman and ghosts
    pacman_ = Pacman({352,322}); //reset pacman and ghosts
    g1_ = Ghost({352,224});
    g2_ = Ghost({352,256});
    g3_ = Ghost({384,224});
    g4_ = Ghost({384,256});
}

void Model::reset_maze_change()
{
    pacman_ = Pacman({352,322}); //reset pacman and ghosts
    g1_ = Ghost({352,224});
    g2_ = Ghost({352,256});
    g3_ = Ghost({384,224});
    g4_ = Ghost({384,256});

    //reset the maze walls variable
    maze_walls_ = m_.get_maze_walls();
}


void Model::set_level(int lvl) {
        m_ = mazes_[lvl%3];
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



    //TODO: CHANGE? Idk maybe this is changed already?? Why did I want to
    // change this? -Brennan
    //go through ghost nexts and ask if pacman hits it
    if(pacman_overlaps_ghost(pacman_, g1_)) {
        //if the pacman does hit the ghost, ask what happens when it does.
        if(pacman_.hit_ghost(g1_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g1_.set_alive(false);
            increment_score(ghost_score_); //add ghost kill score to score
        } else {
            decrement_pacman_lives();
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_, g2_)) {
        if(pacman_.hit_ghost(g2_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g2_.set_alive(false);
            increment_score(ghost_score_); //add ghost kill score to score
        } else {
            decrement_pacman_lives();
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_, g3_)) {
        if(pacman_.hit_ghost(g3_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g3_.set_alive(false);
            increment_score(ghost_score_); //add ghost kill score to score
        } else {
            decrement_pacman_lives();
            return; //return immediately if game over - don't update anything
        }
    }
    if(pacman_overlaps_ghost(pacman_, g4_)) {
        if(pacman_.hit_ghost(g4_)) {
            //pacman hits ghost --> returns true if pacman kills it and
            // false if pacman dies from the ghost
            g4_.set_alive(false);
            increment_score(ghost_score_); //add ghost kill score to score
        } else {
            decrement_pacman_lives();
            return; //return immediately if game over - don't update anything
        }
    }


    if(pacman_overlaps_pellet()) {
        if(m_.all_pellets_eaten()) {
            increment_round();
        }
    }

    if(update_pacman) {
        pacman_ = pacman_.next(dt); //store the result in the pacman for real
    }

    g1_ = g1_.next(dt);
    g2_ = g2_.next(dt);
    g3_ = g3_.next(dt);
    g4_ = g4_.next(dt);
}

// Maze
// Model::maze_() const
// {
//     return m_;
// }

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
    if(!game_over_) {
        pacman_.update_direction(d);
    }
}

int Model::round_num = 0;
bool Model::ate = false;

///GETTERS
/*
int
Model::get_score() {
    return score_;
}
int
Model::get_round_number()
{
    return round_number_;
}
int
Model::get_pacman_lives()
{
    return pacman_lives_;
}
*/

///TESTING FUNCTIONS
