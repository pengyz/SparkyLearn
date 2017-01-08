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
#include "src/graphics/layers/group.h"

#include <FreeImage.h>




using namespace sparky;
using namespace graphics;
using namespace maths;


#define         TEST_50K_SPRITES    0

int main2() {
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
    mat4 transform = maths::mat4::translation(maths::vec3(5.0f, 2.0f, 0));
    Group* group = new Group(transform);
    group->add(new Sprite(0, 0, 6, 3, maths::vec4(1, 1, 1, 1)));

    Group* button = new Group(maths::mat4::translation(maths::vec3(0.5, 0.5, 0)) * mat4::rotation(30.0f, vec3(0, 0, 1)));
    button->add(new Sprite(0, 0, 5, 2, maths::vec4(1, 0, 1, 1)));
    button->add(new Sprite(0.5f, 0.5f, 4, 1, maths::vec4(0.2f, 0.3f, 0.8f, 1)));
    group->add(button);
    layer.add(group);


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
    return 0;
}


int main()
{
    const char* filename = "test.jpg";
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);
    //image width and height
    unsigned int width(0), height(0);
    //OpenGL's image ID to map to
    GLuint gl_texID;

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
        return false;

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    //if the image failed to load, return failure
    if (!dib)
        return false;

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
        return false;

    std::cout << width << ", " << height;

    unsigned int bitPeerPixel = FreeImage_GetBPP(dib);
    std::cout << "BPP: " << bitPeerPixel << std::endl;

    return 0;
}