#pragma once

#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "../maths/maths.h"
#include "shader.h"


#include <GL/glew.h>
#include "texture.h"

namespace sparky {
    namespace graphics {

        class Renderer2D;


        struct VertexData {
            maths::vec3 vertex;
            maths::vec2 uv;
            float tid;
            unsigned int color;
        };


        class Renderable2D
        {
        private:
            maths::vec3 m_Position;
            maths::vec2 m_Size;
            maths::vec4 m_Color;
            std::vector<maths::vec2> m_UV;
            Texture* m_Texture;


        protected:
            Renderable2D() { setUVDefaults(); }

        public:
            Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color) :
                m_Position(position), m_Size(size), m_Color(color) {
                setUVDefaults();
            }

            Renderable2D(maths::vec3 position, maths::vec2 size, Texture* texture) :
                m_Position(position), m_Size(size), m_Texture(texture) {
                setUVDefaults();
            }



            virtual ~Renderable2D() {

            }

            virtual void submit(Renderer2D* renderer) const;

            inline const maths::vec3& getPosition()const { return m_Position; }
            inline const maths::vec2& getSize()const { return m_Size; }
            inline const maths::vec4& getColor()const { return m_Color; }
            inline const std::vector<maths::vec2>& getUV()const { return m_UV; }
            inline const GLuint getTID()const { return m_Texture == nullptr ? 0 : m_Texture->getTID(); }


        private:
            void setUVDefaults()
            {
                m_UV.push_back(maths::vec2(0, 0));
                m_UV.push_back(maths::vec2(0, 1));
                m_UV.push_back(maths::vec2(1, 1));
                m_UV.push_back(maths::vec2(1, 0));
            }


        };
    }
}
