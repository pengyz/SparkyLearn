#include "shader.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "../utils/fileutil.h"

namespace sparky {
    namespace graphics {

        Shader::Shader(const char * vertPath, const char * fragPath) :
            m_VerPath(vertPath), m_FragPath(fragPath)
        {
            m_ShaderID = load();
        }

        Shader::~Shader()
        {
            glDeleteProgram(m_ShaderID);
        }

        void Shader::enable() const
        {
            glUseProgram(m_ShaderID);
        }

        void Shader::disable() const
        {
            glUseProgram(0);
        }

        GLuint Shader::load()
        {
            GLuint program = glCreateProgram();
            GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

            std::string vertSourceString = FileUtils::read_file(m_VerPath);
            std::string fragSourceString = FileUtils::read_file(m_FragPath);

            const char* vertSource = vertSourceString.c_str();
            const char* fragSource = fragSourceString.c_str();

            GLint result;

            glShaderSource(vertex, 1, &vertSource, NULL);
            glCompileShader(vertex);
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
            if (GL_FALSE == result)
            {
                GLint length;
                glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(vertex, length, &length, &error[0]);
                std::cout << "Faile to compile vertex shader: " << &error[0] << std::endl;
                glDeleteShader(vertex);
                return 0;
            }

            glShaderSource(fragment, 1, &fragSource, NULL);
            glCompileShader(fragment);
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
            if (GL_FALSE == result)
            {
                GLint length;
                glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(fragment, length, &length, &error[0]);
                std::cout << "Faile to compile fragment shader: " << &error[0] << std::endl;
                glDeleteShader(fragment);
                return 0;
            }

            glAttachShader(program, vertex);
            glAttachShader(program, fragment);

            glLinkProgram(program);
            glValidateProgram(program);

            glDetachShader(program, vertex);
            glDetachShader(program, fragment);
            
            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return program;
        }



        void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix) {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);

        }
        void Shader::setUniform1f(const GLchar* name, float value) {
            glUniform1f(getUniformLocation(name), value);
        }
        void Shader::setUniform1i(const GLchar* name, int value) {
            glUniform1i(getUniformLocation(name), value);
        }
        void Shader::setUniform1fv(const GLchar * name, float* value, unsigned int count)
        {
            glUniform1fv(getUniformLocation(name), count, value);
        }
        void Shader::setUniform1iv(const GLchar * name, int * value, unsigned int count)
        {
            glUniform1iv(getUniformLocation(name), count, value);
        }
        void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector) {
            glUniform2f(getUniformLocation(name), vector.x, vector.y);
        }
        void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector) {
            glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);

        }
        void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector) {
            glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
        }

        GLuint Shader::getUniformLocation(const GLchar* name) const {
            return glGetUniformLocation(m_ShaderID, name);
        }
    }
}