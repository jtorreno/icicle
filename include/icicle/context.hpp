#pragma once

#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "icicle/renderer.hpp"
#include "icicle/detail/glsl_program.hpp"

namespace icicle
{
    class context
    {
    public:
        ~context();

        static context& instance(int width = 1600, int height = 900, bool fullscreen = false, const std::string& title = "Icicle");

        friend class renderer;
    private:
        context(int width, int height, bool fullscreen, const std::string& title);

        void swap_buffers() noexcept;

        GLFWwindow* window;
        std::unique_ptr<detail::glsl_program> glsl_program_;
    };
}
