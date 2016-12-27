#include "BathRenderer2D.h"
namespace sparky {
    namespace graphics {


        BathRenderer2D::BathRenderer2D() :
            m_VAO(0)
            , m_VBO(0)
            , m_IBO(nullptr)
            , m_IndexCount(0),
            m_Buffer(nullptr)
        {
            init();
        }


        BathRenderer2D::~BathRenderer2D()
        {
            delete m_IBO;
            glDeleteBuffers(1, &m_VBO);
        }

        void BathRenderer2D::init()
        {
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
            glEnableVertexAttribArray(SHADER_COLOR_INDEX);
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            GLuint* indeices = new GLuint[RENDERER_INDICES_SIZE];

            int offset = 0;
            for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
            {
                indeices[i + 0] = offset + 0;
                indeices[i + 1] = offset + 1;
                indeices[i + 2] = offset + 2;

                indeices[i + 3] = offset + 2;
                indeices[i + 4] = offset + 3;
                indeices[i + 5] = offset + 0;

                offset += 4;
            }

            m_IBO = new IndexBuffer(indeices, RENDERER_INDICES_SIZE);
            glBindVertexArray(0);
            delete indeices;
        }


        void BathRenderer2D::submit(Renderable2D* renderable)
        {
            const auto& position = renderable->getPosition();
            const auto& size = renderable->getSize();
            const auto& color = renderable->getColor();

            //left top
            m_Buffer->vertex = position;
            m_Buffer->color = color;
            m_Buffer++;

            //left bottom
            m_Buffer->vertex = maths::vec3(position.x, position.y + size.y, position.z);
            m_Buffer->color = color;
            m_Buffer++;

            //left top
            m_Buffer->vertex = maths::vec3(position.x + size.x, position.y + size.y, position.z);
            m_Buffer->color = color;
            m_Buffer++;

            //right top
            m_Buffer->vertex = maths::vec3(position.x + size.x, position.y, position.z);
            m_Buffer->color = color;
            m_Buffer++;



            m_IndexCount += 6;
        }

        void BathRenderer2D::flush()
        {
            //we should draw all the sprites with the vertex buffer and indicate data.
            glBindVertexArray(m_VAO);
            m_IBO->bind();

            glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

            m_IBO->unbind();
            glBindVertexArray(0);
            m_IndexCount = 0;
        }

        void BathRenderer2D::begin()
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void BathRenderer2D::end()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

    }
}