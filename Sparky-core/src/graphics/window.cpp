#include "window.h"
#include <iostream>


namespace sparky {
    namespace graphics {

        bool Window::m_Keys[MAX_KEYS];
        bool Window::m_MouseButtons[MAX_BUTTONS];
        double Window::mx;
        double Window::my;


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
            glfwSetWindowSizeCallback(m_Window, resize_callback);
            glfwSetKeyCallback(m_Window, key_callback);
            glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
            glfwSetCursorPosCallback(m_Window, cursor_position_callback);
            glfwSwapInterval(0);
            if (glewInit() != GLEW_OK) {
                std::cout << "Could not initialize GLEW!" << std::endl;
                return false;
            }
            std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
            glfwSetWindowUserPointer(m_Window, this);
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

        bool Window::isKeyPressed(unsigned int keycode) const
        {
            if (keycode >= sizeof(m_Keys) / sizeof(bool))
                return false;
            return m_Keys[keycode];
        }

        bool Window::isMouseButtonPressed(unsigned int mouse) const
        {
            if (mouse >= sizeof(m_MouseButtons) / sizeof(bool))
                return false;
            return m_MouseButtons[mouse];
        }

        void Window::getMousePosition(double & x, double & y) const
        {
            x = mx;
            y = my;
        }

        Window::Window(const char * title, int width, int height) :
            m_Title(title), m_Width(width), m_Height(height), m_Window(nullptr)
        {
            if (!init()) {
                std::cout << "Failed to Initialize Window";
            }

            memset(m_Keys, 0, sizeof(m_Keys));
            memset(m_MouseButtons, 0, sizeof(m_MouseButtons));
        }
        Window::~Window()
        {
            glfwTerminate();
        }

        void Window::update()
        {
            GLenum error = glGetError();
            if (GL_NO_ERROR != error)
                std::cout << "OpenGL error: " << error << std::endl;

            glfwPollEvents();
            glfwSwapBuffers(m_Window);
        }


        //callbacks
        void resize_callback(GLFWwindow * window, int width, int height)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            win->m_Width = width;
            win->m_Height = height;
            glViewport(0, 0, width, height);
        }

        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            win->m_Keys[key] = action != GLFW_RELEASE;
        }

        void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            win->m_MouseButtons[button] = action != GLFW_RELEASE;
        }

        void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
        {
            Window* win = (Window*)glfwGetWindowUserPointer(window);
            win->mx = xpos;
            win->my = ypos;
        }


    }
}