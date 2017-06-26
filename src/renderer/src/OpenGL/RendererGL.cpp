#include <cstdio>
#include <glad/glad.h>
#include <OpenGL/RendererGL.h>

using namespace whyte;

void RendererGL::initialize_window()
{
    // TODO: Move window management out to a separate class
    // TODO: Log errors here instead of printf()
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not start! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        // TODO: Auto-detect latest OpenGL version
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

void RendererGL::clear_screen(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RendererGL::finalize()
{
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void RendererGL::tick()
{
    SDL_GL_SwapWindow(window_);
}
