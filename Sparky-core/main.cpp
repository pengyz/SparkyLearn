#include <string>
#include <iostream>
#include <chrono>



#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileutil.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/sprite.h"
#include "src/graphics/bathrenderer2d.h"
#include "src/graphics/staticsprite.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/utils/Timer.h"


using namespace sparky;
using namespace graphics;
using namespace maths;


#define         TEST_50K_SPRITES    0

int main() {
    Window window("Sparky Engine", 960, 540);
    Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    TileLayer layer(shader);
#if TEST_50K_SPRITES
    for (float y = 0; y < 9.0f; y += 0.1)
    {
        for (float x = 0; x < 16.0f; x += 0.1)
        {
            layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f))));
        }
    }
#else
    layer.add(new Sprite(5.0f, 7.0f, 4, 2, maths::vec4(1, 1, 1, 1)));
    layer.push(maths::mat4::translation(maths::vec3(5.0f, 7.0f, 1)));
    layer.add(new Sprite(0.5, 0.5, 1, 1, maths::vec4(1, 0, 1, 1)));
    //layer.pop();


#endif
    int fpsCount = 0;
    Timer timer;
    while (!window.closed()) {
        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader->setUniform2f("light_pos", vec2((float)(x * 16.0f / window.getWidth()), (float)(9.0f - y * 9.0f / window.getHeight())));
        layer.render();
        window.update();
        if (timer.elapsed() < 1000) {
            fpsCount++;
        }
        else
        {
            std::cout << "FPS: " << fpsCount << std::endl;
            fpsCount = 0;
            timer.reset();
        }
    }
}