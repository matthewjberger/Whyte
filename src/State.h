#pragma once

#include <SDL.h>
#include "Subject.h"
#include "Event.h"

namespace whyte
{
    class State : public Subject<Event, EventInfo>
    {
    public:
        virtual ~State() {}

        void start();
        void stop();
        void pause();
        void resume();
        void handle_events(SDL_Event* event);
        void update();

        bool is_running() const { return running_; }
        bool is_paused() const { return paused_; }

    private:
        virtual void on_start() = 0;
        virtual void on_stop() = 0;
        virtual void on_pause() = 0;
        virtual void on_resume() = 0;
        virtual void on_handle_events(SDL_Event* event) = 0;
        virtual void on_update() = 0;

        bool running_ = false;
        bool paused_ = false;
    };
}
