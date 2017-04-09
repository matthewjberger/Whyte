#include "Application.h"

using namespace whyte;

class GameStateB : public State
{
public:
    ~GameStateB() override {}

    void on_start() override {}
    void on_stop() override {}
    void on_pause() override {}
    void on_resume() override {}
    void on_handle_events(SDL_Event* event) override 
    { 
        if (event->key.keysym.sym == SDLK_a)
        {
            EventInfo info;
            info.type = Event::STATE_MACHINE_EVENT;
            info.stateMachine.type = StateMachineEvent::POP_STATE;
            notify(info.type, info);
        } 
    }
    void on_update() override {}
};

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

        if(event->key.keysym.sym == SDLK_p)
        {
            EventInfo info;
            info.type = Event::STATE_MACHINE_EVENT;
            info.stateMachine.type = StateMachineEvent::PUSH_STATE;
            info.stateMachine.stateId = "stateB";
            notify(info.type, info);
        }
    }
    void on_update() override {}
};

int main(int argc, char* args[])
{
    auto state = std::make_unique<GameState>();
    auto stateB = std::make_unique<GameStateB>();
    Application app;
    app.register_state<GameState>("stateA", move(state));
    app.register_state<GameStateB>("stateB", move(stateB));
    app.initialize("stateA");
    app.run();
    return 0;
}