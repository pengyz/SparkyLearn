#include "tilelayer.h"
#include "../bathrenderer2d.h"
#include "../../maths/maths.h"

namespace sparky {
    namespace graphics {

        TileLayer::TileLayer(Shader* shader) :
            Layer(new BathRenderer2D(), shader, maths::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f))
        {
        }


        TileLayer::~TileLayer()
        {
        }

    }
}
