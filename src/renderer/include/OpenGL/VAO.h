#pragma once

#include <OpenGL/GLIncludes.h>

namespace whyre
{
    class VAO
    {
    public:

        VAO();
        ~VAO();

        void bind() const;

        static void unbind();
        static void enable_attribute(GLint location = 0);
        static void disable_attribute(GLint location = 0);
        static void configure_attribute(GLuint index, GLint size, GLenum type,
            GLboolean normalized, GLsizei stride, const GLvoid* pointer);

    private:

        void create();
        void free() const;
        GLuint vertexArray;
    };
}
