#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"
#include <vector>

namespace sparky {
    namespace graphics {


        class Layer
        {
        protected:
            Renderer2D* m_Renderer;
            std::vector<Renderable2D*> m_Renderables;
            Shader* m_Shader;
            maths::mat4 m_ProjectionMatrix;
        protected:
            Layer(Renderer2D* render, Shader* shader, maths::mat4 matrix);
        public:
            ~Layer();
            virtual void add(Renderable2D* renderable);
            virtual void render();


        };

    }
}