#include <glm/gtc/matrix_transform.hpp>

#include "stak/camera.hpp"

using namespace stak;

void stak::camera(const glm::vec3 & position, const glm::vec3 & target)
{
    view = glm::lookAt(position, target, glm::vec3(0, 1, 0));
    projection = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);

    mvp = projection * view * model;
}

glm::mat4 stak::model = glm::mat4(1.0f);
glm::mat4 stak::view = glm::mat4(1.0f);
glm::mat4 stak::projection = glm::mat4(1.0f);

glm::mat4 stak::mvp = glm::mat4(1.0f);
