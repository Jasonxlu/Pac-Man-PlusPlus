#include "controller.hxx"

Controller::Controller()
        : model_(24,16, 32),
        view_(model_)
{ }
//NOTE: Brennan added maze size to constructor

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key)
{

    if (key == ge211::Key::code('q')) {
        quit();
    }

    if(key == ge211::Key::up())
    {
        model_.get_pacman().update_direction({0,-1});

    }

    if(key == ge211::Key::down())
    {
        model_.get_pacman().update_direction({0,1});
    }

    if(key == ge211::Key::left())
    {
        model_.get_pacman().update_direction({-1,0});
    }

    if(key == ge211::Key::right())
    {
        model_.get_pacman().update_direction({1,0});
    }
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}



void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}