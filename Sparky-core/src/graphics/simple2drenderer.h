#pragma once
#include <GL/glew.h>
#include <deque>
#include "../maths/maths.h"
#include "renderable2d.h"
#include "renderer2d.h"

namespace sparky {
    namespace graphics {


        class Simple2DRenderer :public Renderer2D
        {
        public:
            Simple2DRenderer() {

            }
            ~Simple2DRenderer() {
                /*for each (Renderable2D* renderable in m_RenderQueue)
                {
                    delete renderable;
                }*/
                m_RenderQueue.clear();
            }
        private:
            std::deque<Renderable2D*> m_RenderQueue;
        public:
            void submit(Renderable2D* renderable) override;
            void flush() override;
        };

    }
}