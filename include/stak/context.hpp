#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace stak
{
    class context
    {
    public:
        static context& instance(int width = 1600, int height = 900, bool fullscreen = false, const std::string& title = "Bugfree");

        ~context();

        void refresh() noexcept;
        void resize() noexcept;
    private:
        context(int width, int height, bool fullscreen, const std::string& title);

        GLFWwindow* window;
    };
}
