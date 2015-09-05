#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "icicle/camera.hpp"
#include "icicle/context.hpp"

using namespace icicle;

const GLuint camera::mvp_handle = glGetUniformLocation(context::instance().glsl_program(), "mvp");

camera::camera(const glm::vec3& position, const glm::vec3& target, float fov)
{
    mvp = glm::perspective(fov, context::instance().width() / static_cast<float>(context::instance().height()), 0.0625f, 65536.0f) * glm::lookAt(position, target, glm::vec3(0, 1, 0)) * glm::mat4(1.0f);
}

const glm::mat4& camera::bind() const noexcept
{
    glUniformMatrix4fv(mvp_handle, 1, GL_FALSE, glm::value_ptr(mvp));
}
