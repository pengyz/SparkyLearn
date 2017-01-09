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
#include "src/graphics/static_sprite.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/utils/Timer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"


using namespace sparky;
using namespace graphics;
using namespace maths;




int main() {

    srand((unsigned int)time(NULL));
    Window window("Sparky Engine", 960, 540);
    Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");


    TileLayer layer(shader);

    Texture* texObjs[] = {
        new Texture("test.jpg"),
        new Texture("test2.jpg")
    };

    //we must use the same vector size with in the shader.
    GLint texIDs[32] = { 0,1,2,3,4,5,6,7,8,9 };
    shader->enable();
    shader->setUniform1iv("textures", texIDs, sizeof(texIDs));

    //Ìí¼Ósprites
    int index = 0;
    for (float y = -9.0f; y < 9.0f; y += 5)
    {
        for (float x = -16.0f; x < 16.0f; x += 5)
        {
            layer.add(new Sprite(x, y, 4.9f, 4.9f, texObjs[index % 2]));
            index++;
        }
    }

    shader->setUniformMat4("pr_matrix", mat4::orthographic(-16.0, 16.0, -9.0, 9.0, -1.0, 1.0));

    int fpsCount = 0;
    Timer timer;
    while (!window.closed()) {
        window.clear();
        double x, y;
        window.getMousePosition(x, y);
        shader->setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
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
    for (auto tex : texObjs)
    {
        delete tex;
        tex = nullptr;
    }
    return 0;
}
