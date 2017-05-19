#include "State.h"

using namespace whyte;

void State::start()
{
    running = true;
    on_start();
}

void State::stop()
{
    running = false;
    on_stop();
}

void State::pause()
{
    paused = true;
    on_pause();
}

void State::resume()
{
    paused = false;
    on_resume();
}

void State::handle_events(SDL_Event* event)
{
    on_handle_events(event);
}

void State::update()
{
    on_update();
}