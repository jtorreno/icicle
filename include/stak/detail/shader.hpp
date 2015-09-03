#pragma once

#include <string>
#include <type_traits>
#include <vector>

#include <glad/glad.h>

namespace stak
{
    namespace detail
    {
        enum class shader_type : GLenum
        {
            vertex = GL_VERTEX_SHADER,
            fragment = GL_FRAGMENT_SHADER
        };

        template<shader_type S>
        class shader
        {
        public:
            shader(const std::string& shader_source);
            shader(shader<S>&& other) noexcept;

            ~shader();

            operator bool() const noexcept;
            operator GLuint() const noexcept;

            const std::string& info_log() const noexcept;
        private:
            GLuint shader_handle = 0;

            int compile_status = GL_FALSE;
            std::string info_log_;
        };

        using vertex_shader = shader<shader_type::vertex>;
        using fragment_shader = shader<shader_type::fragment>;

        template<shader_type ShaderT>
        shader<ShaderT>::shader(const std::string& shader_source)
        {
            shader_handle = glCreateShader(static_cast<GLenum>(ShaderT));
            glShaderSource(shader_handle, 1, const_cast<const char**>(&static_cast<const char* const&>(shader_source.data())), nullptr); // Fuck Tony's suggestion.
            glCompileShader(shader_handle);

            glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);

            GLint log_length = 0;
            glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_length);

            if (log_length > 1)
            {
                info_log_.reserve(log_length);
                glGetShaderInfoLog(shader_handle, log_length, &log_length, &info_log_[0]);
            }
        }

        template<shader_type ShaderT>
        shader<ShaderT>::shader(shader<ShaderT>&& other) noexcept : shader_handle(other.shader_handle), compile_status(other.compile_status), info_log_(std::move(other.info_log_))
        {
            other.shader_handle = 0;
            other.compile_status = GL_FALSE;
        }

        template<shader_type ShaderT>
        shader<ShaderT>::~shader()
        {
            glDeleteShader(shader_handle);
        }

        template<shader_type ShaderT>
        shader<ShaderT>::operator bool() const noexcept
        {
            return compile_status == GL_TRUE;
        }

        template<shader_type ShaderT>
        shader<ShaderT>::operator GLuint() const noexcept
        {
            return shader_handle;
        }

        template<shader_type ShaderT>
        const std::string& shader<ShaderT>::info_log() const noexcept
        {
            return info_log_;
        }
    }
}
