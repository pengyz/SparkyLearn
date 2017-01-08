#pragma once
#include <string>
#include <GL/glew.h>
#include <FreeImage.h>

namespace sparky {
    namespace graphics {
        class Texture {
        private:
            std::string m_Path;
            GLuint m_TID;
            GLsizei m_Width, m_Height;

        public:
            Texture(std::string& filename);
            Texture(const char* filename);
            ~Texture();
            void bind() const;
            void unbind() const;

            inline const unsigned int getWidth()const { return m_Width; }
            inline const unsigned int getHeight()const { return m_Height; }
            inline const GLuint getTID()const { return m_TID; }


        private:
            GLuint load();

        };
    }
}
