#include <string>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stak/context.hpp"
#include "stak/detail/shader.hpp"
#include "stak/detail/glsl_program.hpp"

using namespace stak;
using namespace stak::detail;

using namespace std::literals::string_literals;

context::context(int width, int height, bool fullscreen, const std::string& title)
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (!window)
    {
        throw std::runtime_error("Failed to create an OpenGL 3.3 context.");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    vertex_shader vertex_shader_("#version 330 core\n"
                                 ""
                                 "in vec3 position;"
                                 "in vec3 normal;"
                                 "in vec2 texcoord;"
                                 ""
                                 "uniform mat4 mvp;"
                                 ""
                                 "void main()"
                                 "{"
                                 "    vec4 v = vec4(position, 1);"
                                 "    gl_Position = mvp * v;"
                                 "}");
    if (!vertex_shader_)
    {
        throw std::runtime_error("Failed to compile vertex shader.\nInfo log:\n\n"s + vertex_shader_.info_log());
    }

    fragment_shader fragment_shader_("#version 330 core\n"
                                     ""
                                     "out vec4 color;"
                                     ""
                                     "void main()"
                                     "{"
                                     "    color = vec4(0.0, 1.0, 0.0, 0.5);"
                                     "}");
    if (!fragment_shader_)
    {
        throw std::runtime_error("Failed to compile fragment shader.\nInfo log:\n\n"s + fragment_shader_.info_log());
    }

    glsl_program_ = {vertex_shader_, fragment_shader_};
    if (!glsl_program_)
    {
        throw std::runtime_error("Failed to link glsl program.\nInfo log:\n\n"s + glsl_program_.info_log());
    }

    glsl_program_.bind();
}


context::~context()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

context& context::instance(int width, int height, bool fullscreen, const std::string& title)
{
    static context instance(width, height, fullscreen, title);

    return instance;
}

void context::swap_buffers() noexcept
{
    glfwSwapBuffers(window);
}
