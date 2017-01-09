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
#include "src/graphics/texture.h"




using namespace sparky;
using namespace graphics;
using namespace maths;


#define         TEST_IMAGE          0


int main() {
#if TEST_IMAGE == 0

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
            //layer.add(new Sprite(x, y, 9.9f, 9.9f, maths::vec4(float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f), float(rand() % 1000 / 1000.0f))));
            layer.add(new Sprite(x, y, 4.9f, 4.9f, texObjs[rand() % 2]));
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

#else
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
#endif

}
