#pragma once

#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "../maths/maths.h"
#include "shader.h"

#include <GL/glew.h>

namespace sparky {
    namespace graphics {

        class Renderable2D
        {
        private:
            maths::vec3 m_Position;
            maths::vec2 m_Size;
            maths::vec4 m_Color;


            VertexArray* m_VertexArray;
            IndexBuffer* m_IndexBuffer;
            Shader& m_Shader;

        public:
            Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader& shader)
                :m_Position(position)
                , m_Size(size)
                , m_Color(color)
                , m_Shader(shader)
            {
                m_VertexArray = new VertexArray();

                GLfloat vertex[] = {
                    0, 0, 0,
                    0, size.y, 0,
                    size.x, size.y, 0,
                    size.x, 0, 0,
                };

                GLfloat colors[] = {
                    color.x,color.y,color.z,color.w,
                    color.x,color.y,color.z,color.w,
                    color.x,color.y,color.z,color.w,
                    color.x,color.y,color.z,color.w,
                };

                m_VertexArray->addBuffer(new Buffer(vertex, 3 * 4, 3), 0);
                m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

                GLushort indices[] = { 0,1,2,2,3,0 };
                m_IndexBuffer = new IndexBuffer(indices, 6);
            }
            
            virtual ~Renderable2D() {
                delete m_VertexArray;
                delete m_IndexBuffer;
            }


            inline const VertexArray* getVAO() { return m_VertexArray; }
            inline const IndexBuffer* getIBO() { return m_IndexBuffer; }
            inline Shader& getShader() { return m_Shader; }

            inline const maths::vec3& getPosition()const { return m_Position; }
            inline const maths::vec2& getSize()const { return m_Size; }
            inline const maths::vec4& getColor()const { return m_Color; }


        };
    }
}
