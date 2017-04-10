#include "../../src/Whyte.h"

using namespace whyte;

class GameState : public State
{
public:
    ~GameState() override {}

    void on_start() override {}
    void on_stop() override {}
    void on_pause() override {}
    void on_resume() override {}
    void on_handle_events(SDL_Event* event) override
    {
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            EventInfo info;
            info.type = Event::APPLICATION_EVENT;
            info.app.type = ApplicationEvent::QUIT;
            notify(info.type, info);
        }
    }

    void on_update() override {}
};

int main(int argc, char* args[])
{
    State* state = new GameState();
    Application app;
    app.initialize(state);
    app.run();
    return 0;
}
