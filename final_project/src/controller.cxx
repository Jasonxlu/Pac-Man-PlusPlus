#include "controller.hxx"

Controller::Controller()
        : model_(24,16),
        view_(model_)

{ }

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
        model_.on_frame(1);
    }

    if(key == ge211::Key::down())
    {

    }

    if(key == ge211::Key::left())
    {

    }

    if(key == ge211::Key::right())
    {

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
    printf("calling on frame in model from controller!");
    model_.on_frame(dt);
}