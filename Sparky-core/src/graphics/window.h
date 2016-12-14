#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace sparky {
    namespace graphics {
        class Window
        {
        private:
            const char* m_Title;
            int m_Width, m_Height;
            GLFWwindow* m_Window;


        public:
            Window(const char* title, int width, int height);
            ~Window();

            inline int getWidth() { return m_Width; }
            inline int getHeight() { return m_Height; }
            void update();
            bool closed() const;
            void clear() const;

        private:
            bool init();

        };
    }
}


