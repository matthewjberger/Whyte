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
        Application() :
            stateMachine_(std::make_unique<StateMachine>()) {}
        ~Application() { finalize(); }

        bool initialize(State*);
        void initialize_window();
        void finalize() const;
        void run() const;

    private:
        void tick() const;

        std::unique_ptr<StateMachine> stateMachine_ = nullptr;
        SDL_Window* window_ = nullptr;
        SDL_GLContext context_ = nullptr;
        bool running = true;
    };
}
