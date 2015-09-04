#include <glm/gtc/matrix_transform.hpp>

#include "icicle/camera.hpp"

using namespace icicle;

camera::camera(const glm::vec3& position, const glm::vec3& target, float aspect_ratio, float fov)
{
    mvp_ = glm::perspective(fov, aspect_ratio, 0.1f, 100.0f) * glm::lookAt(position, target, glm::vec3(0, 1, 0)) * glm::mat4(1.0f);
}

const glm::mat4& camera::mvp() const noexcept
{
    return mvp_;
}
