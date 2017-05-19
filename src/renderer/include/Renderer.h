#pragma once

#include "internal/DllExport.h"

namespace whyte
{
    enum WHYRE_API RENDERING_BACKEND
    {
        BACKEND_OPENGL
    };

    struct WHYRE_API DisplayConfig
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

    class WHYRE_API Renderer
    {
    public:
        virtual ~Renderer() {}

        // TODO: Take in a display config
        // TODO: Make the virtual members private (NVI)
        virtual void initialize_window() = 0;
        virtual void clear_screen(float r, float g, float b, float a) = 0;
        virtual void finalize() = 0;
        virtual void tick() = 0;
    };
}
