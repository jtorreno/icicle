#include <stdexcept>
#include <utility>

#include "stak/renderable.hpp"

using namespace stak;

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

    const auto fail = [&]()
    {
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
        error_string_.append("\nEncountered non-3D vertex coordinates\n");
        fail();
    }

    if (indicessize / static_cast<float>(firstmesh.normals.size()) == 1 / 3)
    {
        error_string_.append("\nEncountered non-3D vertex normals\n");
        fail();
    }

    if (indicessize / static_cast<float>(firstmesh.texcoords.size()) == 1 / 2)
    {
        error_string_.append("\nEncountered non-2D texture coordinates\n");
        fail();
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
