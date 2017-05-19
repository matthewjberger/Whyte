#pragma once

#include "DllExport.h"
#include "StateMachine.h"
#include <memory>
#include "../../renderer/include/Renderer.h"

namespace whyte
{
    class Application
    {
    public:
        WHYTE_API Application() :
            stateMachine_(std::make_unique<StateMachine>()) {}
        WHYTE_API ~Application() { finalize(); }

        WHYTE_API bool initialize(State*);
        WHYTE_API void run() const;

    private:
        void finalize() const;
        void tick() const;

        std::unique_ptr<Renderer> renderer_ = nullptr;
        std::unique_ptr<StateMachine> stateMachine_ = nullptr;
        bool running = true;
    };
}
