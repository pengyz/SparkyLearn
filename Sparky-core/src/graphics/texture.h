#pragma once
#include <string>
#include <GL/eglew.h>
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
            ~Texture();
            void bind() const;
            void unbind() const;

            inline const unsigned int getWidth() { return m_Width; }
            inline const unsigned int getHeight() { return m_Height; }

        private:
            GLuint load();

        };
    }
}
