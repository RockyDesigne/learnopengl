#include "Window.h"
#include "Shader.h"
#include "Square.h"

int main()
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
    float squareVertices[18] = {
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f,  0.5f, 0.f,

            0.5f,  0.5f, 0.f,
            -0.5f,  0.5f, 0.f,
            -0.5f, -0.5f, 0.f
    };
    Square square {squareVertices, sizeof(squareVertices)};

    auto drawShapes {[&square](){square.draw();}};

	while (!glfwWindowShouldClose(window.get_windowPtr()))
	{
		window.update({drawShapes});
        ourShader.use();

	}

	return 0;
}