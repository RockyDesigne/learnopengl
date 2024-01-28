#include <memory>
#include "Window.h"
#include "Shader.h"
#include "Square.h"
#include "Triangle.h"
#ifndef LA_IMPLEMENTATION
#define LA_IMPLEMENTATION
#endif
#include "la.h"

int main1()
{
    Window window{ 0,0,800,600 };

    window.set_key_callback([](GLFWwindow* win, int key, int scancode, int action, int mods)
                            {
                                switch (key)
                                {
                                    case GLFW_KEY_ESCAPE:
                                    {
                                        if (action == GLFW_PRESS) {
                                            glfwSetWindowShouldClose(win, true);
                                        }
                                        break;
                                    }
                                }
                            });

    Shader ourShader{"vertex.glsl", "fragment.glsl"};

    ourShader.use();
    ourShader.set_float("offset", 0.25f);

    constexpr int size = 8;
    std::vector<std::vector<std::unique_ptr<Square>>> checkerboard;
    for (int i = 0; i < size; ++i) {
        checkerboard.emplace_back();
        for (int j = 0; j < size; ++j) {
            checkerboard[i].emplace_back();
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            V3f topLeft(-1.0f + i * 2.0f / size, 1.0f - j * 2.0f / size, 0.f);
            V3f bottomRight(-1.0f + (i + 1) * 2.0f / size, 1.0f - (j + 1) * 2.0f / size, 0.f);

            checkerboard[i][j] = std::make_unique<Square>(topLeft, bottomRight);

            if ((i + j) % 2 == 0) {
                checkerboard[i][j]->setColor(V4f(0.f, 0.f, 0.f,1.f)); // Black
            } else {
                checkerboard[i][j]->setColor(V4f(1.f, 1.f, 1.f,1.f)); // White
            }
        }
    }

    auto drawShapes = [&checkerboard, &ourShader](){
        for (auto& row : checkerboard) {
            for (auto& square : row) {
                ourShader.set_vec4("ourColor", square->getColor());
                square->draw();
            }
        }
    };


    while (!glfwWindowShouldClose(window.get_windowPtr()))
    {
        window.update({drawShapes});
        ourShader.use();

    }

    return 0;
}