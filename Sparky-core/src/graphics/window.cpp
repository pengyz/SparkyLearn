#include "window.h"
#include <iostream>
#include <functional>


namespace sparky {
    namespace graphics {
        bool Window::init()
        {
            if (!glfwInit())
            {
                std::cout << "Failed to Initialize GLFW.";
                return false;
            }

            m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
            if (!m_Width)
            {
                glfwTerminate();
                std::cout << "Failed to create glfwWindow";
                return false;
            }
            glfwMakeContextCurrent(m_Window);
            glfwSetWindowSizeCallback(m_Window, [](GLFWwindow * window, int width, int height)->void {
                glViewport(0, 0, width, height);
            });
            if (glewInit() != GLEW_OK) {
                std::cout << "Could not initialize GLEW!" << std::endl;
                return false;
            }

            std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;


            return true;
        }

        bool Window::closed() const
        {
            return glfwWindowShouldClose(m_Window) == 1;
        }

        void Window::clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        Window::Window(const char * title, int width, int height) :
            m_Title(title), m_Width(width), m_Height(height), m_Window(nullptr)
        {
            if (!init()) {
                std::cout << "Failed to Initialize Window";
            }
        }
        Window::~Window()
        {
            glfwTerminate();
        }

        void Window::update()
        {
            glfwPollEvents();
            glfwSwapBuffers(m_Window);
        }

    }
}