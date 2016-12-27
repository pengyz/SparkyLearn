#pragma once
#include <GL/glew.h>

namespace sparky {
    namespace graphics {
        class IndexBuffer
        {
        private:
            GLuint m_BufferID;
            GLuint m_Count;
        public:
            IndexBuffer(GLuint *data, GLsizei count);
            ~IndexBuffer();

            inline GLuint getCount() const { return m_Count; }
            void bind() const;
            void unbind() const;
        };
    }
}
