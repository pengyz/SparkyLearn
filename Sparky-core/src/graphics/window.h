#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace sparky {
    namespace graphics {
#define MAX_KEYS            1024
#define MAX_BUTTONS         64

        class Window
        {
        private:
            const char* m_Title;
            int m_Width, m_Height;
            GLFWwindow* m_Window;

            static bool m_Keys[MAX_KEYS];
            static bool m_MouseButtons[MAX_BUTTONS];
            static double mx, my;

        public:
            Window(const char* title, int width, int height);
            ~Window();

            void update();
            bool closed() const;
            void clear() const;

            inline int getWidth() { return m_Width; }
            inline int getHeight() { return m_Height; }
            
            bool isKeyPressed(unsigned int keycode) const;
            bool isMouseButtonPressed(unsigned int mouse) const;
            void getMousePosition(double&x, double &y) const;

        private:
            bool init();
            friend void resize_callback(GLFWwindow* window, int width, int height);
            friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
            friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
            friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

        };
    }
}


