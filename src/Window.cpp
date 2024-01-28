//
// Created by HORIA on 17.01.2024.
//
#include "Window.h"

Window::Window(int startingX, int startingY, int width, int height)
        : m_startingX{startingX}, m_startingY{startingY}, m_width{width}, m_height{height}
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windowPtr = glfwCreateWindow(m_width, m_height, "Window", nullptr, nullptr);
    glfwMakeContextCurrent(m_windowPtr);
    load_gl();
    glfwSetFramebufferSizeCallback(m_windowPtr, [](GLFWwindow* win, int w, int h)
    {
        glViewport(0, 0, w, h);
    });
}

Window::~Window() {
    glfwTerminate();
}

int Window::get_startingX() const { return m_startingX; }

int Window::get_startingY() const { return m_startingY; }

int Window::get_height() const { return m_height; }

GLFWwindow *Window::get_windowPtr() const { return m_windowPtr; }

void Window::load_gl() {
    gladLoadGLLoader((reinterpret_cast<GLADloadproc>(glfwGetProcAddress)));
}

void Window::set_viewport() {
    glViewport(m_startingX, m_startingY, m_width, m_height);
}

void Window::update(const std::vector<std::function<void()>>& drawFunctions) {
    glfwGetWindowSize(m_windowPtr,&m_width, &m_height);
    glClear(GL_COLOR_BUFFER_BIT);
    //draw stuff
    std::for_each(drawFunctions.begin(),drawFunctions.end(),[](auto& f){f();});
    glfwSwapBuffers(m_windowPtr);
    glfwPollEvents();
}

void Window::set_key_callback(void (*f)(GLFWwindow *, int, int, int, int)) {
    glfwSetKeyCallback(m_windowPtr, f);
}
