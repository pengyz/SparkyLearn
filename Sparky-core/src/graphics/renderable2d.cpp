#include "renderable2d.h"
#include "renderer2d.h"


namespace sparky {
    namespace graphics {
        void Renderable2D::submit(Renderer2D* renderer) const {
            renderer->submit(this);
        }
    }
}