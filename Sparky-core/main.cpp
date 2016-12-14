#include "src/graphics/window.h"
#include <iostream>



int main() {
    using namespace sparky;
    using namespace graphics;
    Window window("sparky engine", 800, 600);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    while (!window.closed()) {

        window.clear();
#if 0
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
#endif

        glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

        window.update();
    }


}