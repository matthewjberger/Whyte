#pragma once

#include "StateMachine.h"
#include <memory>

namespace whyte
{
    enum RENDERING_BACKEND
    {
        BACKEND_OPENGL
    };

    struct DisplayConfig
    {
        int x;
        int y;
        int width;
        int height;
        int bpp;
        bool fullscreen;
        bool visible;
        RENDERING_BACKEND backend;
    };

    class Application
    {
    public:
        Application();
        ~Application() { finalize(); }

        bool initialize(const std::string);

        template <typename StateType>
        void register_state(const std::string, std::unique_ptr<StateType>);
        void unregister_state(const std::string) const;

        void run() const;

    private:
        void initialize_window();
        void finalize() const;
        void tick() const;

        std::unique_ptr<StateMachine> stateMachine_ = nullptr;
        SDL_Window* window_ = nullptr;
        SDL_GLContext context_ = nullptr;
        bool running = true;
    };

    template <typename StateType>
    void Application::register_state(const std::string stateId, std::unique_ptr<StateType> state)
    {
        stateMachine_->register_state<StateType>(stateId, move(state));
    }
}
