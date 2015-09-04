#pragma once

#include <string>
#include <vector>

#include <tinyobjloader/tiny_obj_loader.h>

namespace icicle
{
    class renderable
    {
    public:
        renderable(const std::string& path);

        operator bool() const noexcept;

        const std::string& error_string() const noexcept;

        const std::vector<tinyobj::mesh_t>& meshes() const noexcept;
        const std::vector<tinyobj::material_t>& materials() const noexcept;
    private:
        bool load_status;
        std::string error_string_;

        std::vector<tinyobj::mesh_t> meshes_;
        std::vector<tinyobj::material_t> materials_;
    };
}
