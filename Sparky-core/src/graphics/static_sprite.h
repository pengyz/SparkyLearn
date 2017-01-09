#pragma once

#include "renderable2d.h"
#include "../maths/maths.h"
#include "buffers/vertexarray.h"
#include "buffers/indexbuffer.h"


namespace sparky {
    namespace graphics {


        class StaticSprite :public Renderable2D
        {
        private:
            Shader m_Shader;
            VertexArray* m_VertexArray;
            IndexBuffer* m_IndexBuffer;

        public:
            StaticSprite(float x, float y, float width, float height, maths::vec4 color, const Shader& shader);
            ~StaticSprite();

            inline const VertexArray* getVAO() { return m_VertexArray; }
            inline const IndexBuffer* getIBO() { return m_IndexBuffer; }
            inline Shader& getShader() { return m_Shader; }
        };
    }
}
