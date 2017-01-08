#pragma once
#include <GL/glew.h>
#include "../maths/mat4.h"
#include "../maths/vec2.h"
#include "../maths/vec3.h"



namespace sparky {
    namespace graphics {
        class Shader {
        private:
            GLuint m_ShaderID;
            const char* m_VerPath, *m_FragPath;
        public:
            Shader(const char* vertPath, const char* fragPath);
            ~Shader();

            void enable() const;
            void disable() const;

            void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
            void setUniform1f(const GLchar* name, float value);
            void setUniform1i(const GLchar* name, int value);
            void setUniform1fv(const GLchar* name, float* value, unsigned int count);
            void setUniform1iv(const GLchar* name, int* value, unsigned int count);
            void setUniform2f(const GLchar* name, const maths::vec2& vector);
            void setUniform3f(const GLchar* name, const maths::vec3& vector);
            void setUniform4f(const GLchar* name, const maths::vec4& vector);


        private:
            GLuint load();
            GLuint getUniformLocation(const GLchar* name) const;

        };
    }
}
