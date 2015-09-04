#pragma once

#include <string>

#include <glad/glad.h>

#include "stak/detail/shader.hpp"

namespace stak
{
    namespace detail
    {
        class glsl_program
        {
        public:
            glsl_program();
            glsl_program(const vertex_shader& vertex_shader_, const fragment_shader& fragment_shader_);
            glsl_program(glsl_program&& other) noexcept;

            glsl_program & operator=(glsl_program&& other) noexcept;

            ~glsl_program();

            operator bool() const noexcept;
            operator GLint() const noexcept;

            const std::string& info_log() const noexcept;
            const std::string& shader_info_log(shader_type type) const;

            void bind() noexcept;
        private:
            GLuint program_handle;
            GLuint matrix_handle;

            GLint link_status;
            std::string info_log_;

            const std::string vertex_shader_info_log;
            const std::string fragment_shader_info_log;
        };
    }
}
