#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace stak
{
    class context
    {
    public:
        ~context();

        static context& instance(int width = 1600, int height = 900, bool fullscreen = false, const std::string& title = "Stak");

        void swap_buffers() noexcept;
        void clear() noexcept;
    private:
        context(int width, int height, bool fullscreen, const std::string& title);

        GLFWwindow* window;
        detail::glsl_program glsl_program_
    };
}
