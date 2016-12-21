#include "shader.h"
#include <iostream>
#include <string>
#include <vector>
#include "../utils/fileutil.h"

using namespace sparky;
using namespace graphics;

Shader::Shader(const char * vertPath, const char * fragPath) :
    m_VerPath(vertPath), m_FragPath(fragPath)
{
    m_ShaderID = load();
}

GLuint Shader::load()
{
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertSource = read_file(m_VerPath).c_str();
    const char* fragSource = read_file(m_FragPath).c_str();

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

}
