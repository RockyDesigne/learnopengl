//
// Created by HORIA on 17.01.2024.
//

#ifndef LEARNGL_WINDOW_H
#define LEARNGL_WINDOW_H
#include <glad.h>
#include <glfw3.h>
#include <vector>
#include <functional>

class Window
{
public:
    Window(int startingX=0, int startingY=0, int width=800, int height=600);
    ~Window();
    //getters
    [[nodiscard]] int get_startingX() const;
    int get_startingY() const;
    [[nodiscard]] int get_width() const { return m_width; }
    int get_height() const;
    GLFWwindow* get_windowPtr() const;
    //functions
    static void load_gl();

    void set_viewport();

    void update(const std::vector<std::function<void()>>& drawFunctions);

    void set_key_callback(void(*f)(GLFWwindow* win,int key, int scancode, int action, int mods));

private:
    int m_startingX{};
    int m_startingY{};
    int m_width{};
    int m_height{};
    GLFWwindow* m_windowPtr{};
};

#endif //LEARNGL_WINDOW_H
