#include <stdexcept>
#include <utility>

#include "icicle/renderable.hpp"

using namespace icicle;

renderable::renderable(const std::string& path) : load_status(false)
{
    std::vector<tinyobj::shape_t> shapes;

    error_string_ = tinyobj::LoadObj(shapes, materials_, path.c_str());
    meshes_.reserve(shapes.size());

    for(auto&& shape : shapes)
    {
        meshes_.emplace_back(std::move(shape.mesh));
    }

    if (!error_string_.empty())
    {
        return;
    }

    load_status = true;

    const auto fail = [&](const char * encountered_what)
    {
        error_string_.append("\nEncountered ").append(encountered_what) += '\n';

        meshes_.clear();
        meshes_.shrink_to_fit();

        materials_.clear();
        materials_.shrink_to_fit();

        load_status = false;
    };

    const auto& firstmesh = meshes_.at(0);
    const auto& indicessize = firstmesh.indices.size();

    if (indicessize / static_cast<float>(firstmesh.positions.size()) == 1 / 3)
    {
        fail("non-3D vertex coordinates");
    }

    if (indicessize / static_cast<float>(firstmesh.normals.size()) == 1 / 3)
    {
        fail("non-3D vertex normals");
    }

    if (indicessize / static_cast<float>(firstmesh.texcoords.size()) == 1 / 2)
    {
        fail("non-2D texture coordinates");
    }
}

renderable::operator bool() const noexcept
{
    return load_status;
}

const std::string& renderable::error_string() const noexcept
{
    return error_string_;
}

const std::vector<tinyobj::mesh_t>& renderable::meshes() const noexcept
{
    return meshes_;
}

const std::vector<tinyobj::material_t>& renderable::materials() const noexcept
{
    return materials_;
}
