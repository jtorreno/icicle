#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace icicle
{
    class camera
    {
    public:
        camera(const glm::vec3& position, const glm::vec3& target, float fov);

        const glm::mat4& bind() const noexcept;
    private:
        static const GLuint mvp_handle;

        glm::mat4 mvp;
    };
}
