#include "Application.h"
#include "StateMachine.h"
#include "Renderer/OpenGL/RendererGL.h"

using namespace whyte;

bool Application::initialize(State* initialState)
{
    try
    {
        // TODO: init renderer based on display config
        renderer_ = std::make_unique<RendererGL>();
        renderer_->initialize_window();
        stateMachine_->change_state(initialState);
        stateMachine_->register_observer(Event::APPLICATION_EVENT, [this](const EventInfo& info)
        {
            if (info.app.type == ApplicationEvent::QUIT)
            {
                running = false;
            }
        });
    }
    catch (...)
    {
        // TODO: Perform logging here
        return false;
    }
    return true;
}

void Application::tick() const
{
    static SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        stateMachine_->handle_events(&event);
    }
    stateMachine_->update();
}

void Application::run() const
{
    SDL_StartTextInput();
    while (running)
    {
        tick();
        renderer_->clear_screen(0.97f, 0.97f, 1.0f, 1.0f);
        renderer_->tick();
    }
    SDL_StopTextInput();
}

void Application::finalize() const
{
    renderer_->finalize();
}
