#pragma once
#include <GL/glew.h>



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

        private:
            GLuint load();


        };
    }
}
