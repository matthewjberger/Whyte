#pragma once

#include "Subject.h"
#include "Event.h"
#include "DllExport.h"
#include <SDL.h>

namespace whyte
{
    class State : public Subject<Event, EventInfo>
    {
    public:
        virtual ~State() {}

        WHYTE_API void start();
        WHYTE_API void stop();
        WHYTE_API void pause();
        WHYTE_API void resume();
        WHYTE_API void handle_events(SDL_Event* event);
        WHYTE_API void update();

        WHYTE_API bool is_running() const { return running; }
        WHYTE_API bool is_paused() const { return paused; }

    private:
        virtual void on_start() = 0;
        virtual void on_stop() = 0;
        virtual void on_pause() = 0;
        virtual void on_resume() = 0;
        virtual void on_handle_events(SDL_Event* event) = 0;
        virtual void on_update() = 0;

        bool running = false;
        bool paused = false;
    };
}
