#include <vector>

#include <tinyobjloader/tiny_obj_loader.h>

#include "stak/renderer.hpp"
#include "stak/context.hpp"
#include "stak/camera.hpp"

using namespace stak;

renderer::renderer() noexcept : vertex_buffer_object(0), vertex_array_object(0)
{
    glGenBuffers(1, &vertex_buffer_object);
    glGenVertexArrays(1, &vertex_array_object);
}

renderer::renderer(renderer&& other) noexcept : vertex_data(std::move(other.vertex_data)), vertex_buffer_object(other.vertex_buffer_object), vertex_array_object(other.vertex_array_object)
{
    other.vertex_buffer_object = 0;
    other.vertex_array_object = 0;
}

renderer::~renderer()
{
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteVertexArrays(1, &vertex_array_object);
}

void renderer::load(const renderable& renderable_)
{
    for (const auto& mesh : renderable_.meshes())
    {
        for (const auto& index : mesh.indices)
        {
            vertex_data.push_back(mesh.positions[index * 3]);
            vertex_data.push_back(mesh.positions[index * 3 + 1]);
            vertex_data.push_back(mesh.positions[index * 3 + 2]);

            vertex_data.push_back(mesh.normals[index * 3]);
            vertex_data.push_back(mesh.normals[index * 3 + 1]);
            vertex_data.push_back(mesh.normals[index * 3 + 2]);

            vertex_data.push_back(mesh.normals[index * 2]);
            vertex_data.push_back(mesh.normals[index * 2 + 1]);
        }
    }

    glBindVertexArray(vertex_array_object);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(6 * sizeof(float)));
}

void renderer::render(const camera& camera_) const noexcept
{
    GLuint matrix_handle = glGetUniformLocation(programID, "mvp")
    glUniformMatrix4fv(matrix_handle, 1, GL_FALSE, glm::value_ptr(camera_.mvp()));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, vertex_data.size() / 8);

    context::instance().swap_buffers();
}
