#pragma once

#include <glm/glm.hpp>

namespace stak
{
    class camera
    {
    public:
        camera(const glm::vec3& position, const glm::vec3& target, float aspect_ratio, float fov);

        const glm::mat4& mvp() const noexcept;
    private:
        glm::mat4 mvp_;
    };
}
