#include <stdexcept>

#include "icicle/context.hpp"
#include "icicle/detail/shader.hpp"

using namespace icicle;
using namespace icicle::detail;

using namespace std::literals::string_literals;

context::context(int width, int height, bool fullscreen, const std::string& title) : width_(width), height_(height)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width_, height_, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (!window)
    {
        throw std::runtime_error("Failed to create an OpenGL 3.3 context.");
    }

    glfwSetInputMode(window, GLFW_CURSOR_DISABLED, GL_TRUE);

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

    glsl_program_ = std::make_unique<glsl_program>(vertex_shader_, fragment_shader_);

    if (!*glsl_program_)
    {
        throw std::runtime_error("Failed to link glsl program.\nInfo log:\n\n"s + glsl_program_ -> info_log());
    }

    glsl_program_ -> bind();

    glEnable(GL_DEPTH_TEST);
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

bool context::should_close() const noexcept
{
    return glfwWindowShouldClose(window);
}

void context::resize(unsigned int width, unsigned int height) noexcept
{
    glfwSetWindowSize(window, width, height);
}

unsigned int context::width() const noexcept
{
    return width_;
}

unsigned int context::height() const noexcept
{
    return height_;
}

void context::set_title(std::string new_title) noexcept
{
    glfwSetWindowTitle(window, new_title.c_str());
}

bool context::key_is_depressed(unsigned int key) const noexcept
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void context::swap_buffers() noexcept
{
    glfwSwapBuffers(window);
}

const glsl_program& context::glsl_program() const noexcept
{
    return *glsl_program_;
}
