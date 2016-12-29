#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include <string>
#include "src/utils/fileutil.h"
#include "src/graphics/shader.h"
#include <iostream>
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/sprite.h"
#include "src/graphics/bathrenderer2d.h"
#include "src/graphics/staticsprite.h"
#include "src/graphics/simple2drenderer.h"
#include <vector>
#include <time.h>
#include "src/graphics/layers/tilelayer.h"

#define BATH_RENDERER       1

#if BATH_RENDERER
#define RendererClass       BathRenderer2D
#define SpriteClass         Sprite
#else
#define RendererClass       Simple2DRenderer
#define SpriteClass         StaticSprite
#endif


int main() {
    using namespace sparky;
    using namespace graphics;
    using namespace maths;

    //srand(time(NULL));

    Window window("Sparky Engine", 960, 540);

    Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    TileLayer layer(shader);
    for (float y = 0; y < 9.0f; y++)
    {
        for (float x = 0; x < 16.0f; x++)
        {
            layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f))));
        }
    }

    while (!window.closed()) {

        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader->setUniform2f("light_pos", vec2((float)(x * 16.0f / window.getWidth()), (float)(9.0f - y * 9.0f / window.getHeight())));
        layer.render();
        window.update();
    }
}