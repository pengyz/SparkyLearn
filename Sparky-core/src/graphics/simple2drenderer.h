#pragma once
#include <GL/glew.h>
#include <deque>
#include "../maths/maths.h"
#include "renderable2d.h"
#include "renderer2d.h"
#include "staticsprite.h"


namespace sparky {
    namespace graphics {


        class Simple2DRenderer :public Renderer2D
        {
        private:
            std::deque<Renderable2D*> m_RenderQueue;
        public:
            void submit(Renderable2D* renderable) override;
            void flush() override;
        };

    }
}