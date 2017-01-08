#include "BathRenderer2D.h"
#include <recdefs.h>
#include "renderable2d.h"



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
            glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);

            glEnableVertexAttribArray(SHADER_UV_INDEX);
            glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));

            glEnableVertexAttribArray(SHADER_TID_INDEX);
            glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));

            glEnableVertexAttribArray(SHADER_COLOR_INDEX);
            glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

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


        void BathRenderer2D::submit(const Renderable2D* renderable)
        {
            const auto& position = renderable->getPosition();
            const auto& size = renderable->getSize();
            const auto& color = renderable->getColor();
            const auto& uv = renderable->getUV();
            const auto tid = renderable->getTID();

            unsigned int c = 0;
            float ts = 0.0f;
            if (tid > 0)
            {
                bool bFound = false;
                auto pos = find(m_TextureSlots.begin(), m_TextureSlots.end(), tid);
                if (pos != m_TextureSlots.end()) {
                    ts = float(pos - m_TextureSlots.begin() + 1);
                }
                else
                {
                    //TODO: not found and why we should check the current texture size??????
                    if (m_TextureSlots.size() >= 32)
                    {

                        end();
                        flush();
                        begin();
                    }
                    m_TextureSlots.push_back(tid);
                    ts = float(m_TextureSlots.size());
                }
            }
            else {
                int r = int(color.x * 255);
                int g = int(color.y * 255);
                int b = int(color.z * 255);
                int a = int(color.w * 255);
                c = a << 24 | b << 16 | g << 8 | r;
            }

            const auto& transformation = *m_BackTransform;
            //left top
            m_Buffer->vertex = transformation * position;
            m_Buffer->color = c;
            m_Buffer->uv = uv[0];
            m_Buffer->tid = ts;
            m_Buffer++;

            //left bottom
            m_Buffer->vertex = transformation * maths::vec3(position.x, position.y + size.y, position.z);
            m_Buffer->color = c;
            m_Buffer->uv = uv[1];
            m_Buffer->tid = ts;
            m_Buffer++;

            //left top
            m_Buffer->vertex = transformation * maths::vec3(position.x + size.x, position.y + size.y, position.z);
            m_Buffer->color = c;
            m_Buffer->uv = uv[2];
            m_Buffer->tid = ts;
            m_Buffer++;

            //right top
            m_Buffer->vertex = transformation * maths::vec3(position.x + size.x, position.y, position.z);
            m_Buffer->color = c;
            m_Buffer->uv = uv[3];
            m_Buffer->tid = ts;
            m_Buffer++;


            m_IndexCount += 6;
        }

        void BathRenderer2D::flush()
        {

            for (int i = 0; i < m_TextureSlots.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
            }

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