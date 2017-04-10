#pragma once

#include "DllExport.h"
#include "StateMachine.h"
#include <memory>
#include "Renderer/Renderer.h"

namespace whyte
{
    class WHYTE_API Application
    {
    public:
        Application() :
            stateMachine_(std::make_unique<StateMachine>()) {}
        ~Application() { finalize(); }

        bool initialize(State*);
        void run() const;

    private:
        void finalize() const;
        void tick() const;

        std::unique_ptr<Renderer> renderer_ = nullptr;
        std::unique_ptr<StateMachine> stateMachine_ = nullptr;
        bool running = true;
    };
}
