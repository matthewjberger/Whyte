#include "Application.h"
#include "StateMachine.h"
#include <glad/glad.h>

using namespace whyte;

Application::Application()
{
    stateMachine_ = std::make_unique<StateMachine>();
    stateMachine_->register_observer(Event::APPLICATION_EVENT, [this](const EventInfo& info)
    {
        if (info.app.type == ApplicationEvent::QUIT)
        {
            running = false;
        }
    });
}

bool Application::initialize(const std::string initialStateId) 
{
    try
    {
        initialize_window();
        stateMachine_->change_state(initialStateId);
    }
    catch( ... )
    {
        // TODO: Perform logging here
        return false;
    }
    return true;
}

void Application::initialize_window() 
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not start! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        // This should be enabled if using the core profile for modern OpenGL
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window_ = SDL_CreateWindow("Whyte", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (window_ == nullptr)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            context_ = SDL_GL_CreateContext(window_);
            if (context_ == nullptr) 
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                //Initialize GLAD
                gladLoadGLLoader(SDL_GL_GetProcAddress);

                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }
            }
        }
    }
}

void Application::unregister_state(const std::string stateId) const
{
    stateMachine_->unregister_state(stateId);
}

void Application::finalize() const
{
    SDL_DestroyWindow(window_);
    SDL_Quit();
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

        // Clear the screen
        glClearColor(0.94f, 0.94f, 1.0f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(window_);
    }
    SDL_StopTextInput();
}