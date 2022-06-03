#pragma once

#include "view.hxx"


#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key(ge211::Key) override;

    //
    // These three “forwarding” member functions are called by the GE211
    // framework and delegate to the other components (model or view).
    // This is because GE211 only knows about the controller, and thus
    // the controller has to mediate between GE211 and the model and
    // view.
    //

    /// The GE211 framework calls this to updates the game state to
    /// reflect the passage of time. This function is passed `dt`, the
    /// elapsed time in seconds since the previous frame. The
    /// implementation in controller.cxx delegates to model.on_frame().
    void on_frame(double dt) override;

    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
};
