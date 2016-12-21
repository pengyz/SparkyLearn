#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include <string>
#include "src/utils/fileutil.h"
#include <iostream>



int main() {
    using namespace sparky;
    using namespace graphics;
    using namespace maths;

    Window window("sparky engine", 800, 600);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vec3 vec(10, 12, 22);
    std::cout << "equals " << (vec != vec3(10, 12, 1)) << std::endl;
    std::cout << "vec4 " << vec4(1, 2, 3, 4)* vec4(4, 32, 3, 55) << std::endl;

    mat4 position = mat4::translation(vec3(1, 2, 3));
    position *= position;

    vec4 column3 = position.columns[3];
    std::cout << column3 << std::endl;


    while (!window.closed()) {

        window.clear();

        if (window.isKeyPressed(GLFW_KEY_A)) {
            std::cout << "Key A Pressed " << std::endl;
        }
        if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            std::cout << "Mouse Button Left Pressed " << std::endl;
        }

        double x, y;
        window.getMousePosition(x, y);
        std::cout << x << "," << y << std::endl;

#if 1
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
#else
        glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif

        window.update();
    }


}