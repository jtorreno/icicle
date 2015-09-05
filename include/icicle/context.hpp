#pragma once

#include <array>
#include <string>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "icicle/renderer.hpp"
#include "icicle/camera.hpp"
#include "icicle/detail/glsl_program.hpp"

namespace icicle
{
    class context
    {
    public:
        ~context();

        static context& instance(int width = 1600, int height = 900, bool fullscreen = false, const std::string& title = "Icicle");

        bool should_close() const noexcept;

        void resize(unsigned int width, unsigned int height) noexcept;
        void set_title(std::string new_title) noexcept;

        unsigned int width() const noexcept;
        unsigned int height() const noexcept;

        bool key_is_depressed(unsigned int key) const noexcept;

        friend class renderer;
        friend class camera;
    private:
        context(int width, int height, bool fullscreen, const std::string& title);

        void swap_buffers() noexcept;

        const detail::glsl_program& glsl_program() const noexcept;

        GLFWwindow* window;

        unsigned int width_;
        unsigned int height_;
        
        std::unique_ptr<detail::glsl_program> glsl_program_;
    };
}
