#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stak/renderer.hpp"

namespace stak
{
    class context
    {
    public:
        ~context();

        static context& instance(int width = 1600, int height = 900, bool fullscreen = false, const std::string& title = "Stak");

        friend class renderer;
    private:
        context(int width, int height, bool fullscreen, const std::string& title);

        void swap_buffers() noexcept;

        GLFWwindow* window;
        detail::glsl_program glsl_program_;
    };
}
