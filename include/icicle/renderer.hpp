#pragma once

#include <vector>

#include <glad/glad.h>

#include "icicle/renderable.hpp"
#include "icicle/camera.hpp"

namespace icicle
{
    class renderer
    {
    public:
        renderer() noexcept;
        renderer(renderer&& other) noexcept;

        ~renderer();

        void load(const renderable& renderable_);
        void render(const camera& camera_) const noexcept;
    private:
        std::vector<float> vertex_data;

        GLuint vertex_buffer_object;
        GLuint vertex_array_object;
    };
}
