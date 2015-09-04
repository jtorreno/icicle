#pragma once

#include <glm/glm.hpp>

namespace stak
{
    void camera(glm::vec3 position, glm::vec3 target);

    extern glm::mat4 model;
    extern glm::mat4 projection;
    extern glm::mat4 view;

    extern glm::mat4 mvp;
}
