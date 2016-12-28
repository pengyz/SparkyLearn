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

    srand(time(NULL));

    Window window("Sparky Engine", 960, 540);

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.enable();

    maths::mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
    shader.setUniformMat4("pr_matrix", ortho);

    shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
    shader.setUniform4f("colour", vec4(0.5f, 0.3f, 0.8f, 1.0f));

    RendererClass renderer;
    std::vector<SpriteClass*> sprites;
    for (float y = 0; y < 9.0f; y++)
    {
        for (float x = 0; x < 16.0f; x++)
        {
            sprites.push_back(new SpriteClass(x, y, 0.9, 0.9, maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f)
#if BATH_RENDERER == 0
                , shader
#endif
            ));
        }
    }

    while (!window.closed()) {

        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / window.getWidth()), (float)(9.0f - y * 9.0f / window.getHeight())));
        renderer.begin();
        for (int i = 0; i < sprites.size(); i++)
        {
            renderer.submit(sprites[i]);
        }
        renderer.end();
        renderer.flush();

        window.update();
    }


}