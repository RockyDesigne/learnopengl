#include <glad.h>
#include <glfw3.h>
#include <random>
#include <vector>

struct Vector4f
{
	Vector4f(float x, float y, float z, float w) : m_x{x}, m_y{y}, m_z{z}, m_w{w} {}
	void set_vector(float x, float y, float z, float w)
	{
				m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}
	float m_x, m_y, m_z, m_w;
	
};

class Triangle
{
public:
	float vertices[9] = {
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.f, 0.5f, 0.f
		};
private:
};

class VertexShader
{
public:
	VertexShader(const Triangle& triangle) : m_data{triangle}
	{
		glGenVertexArrays(1, &m_VAO);
		add_buffer();
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vertexShader, 1, &m_vertexShaderSource, nullptr);
		glCompileShader(m_vertexShader);
	}
	~VertexShader()
	{
		glDeleteShader(m_vertexShader);
	}
	void add_buffer()
	{
		glBindVertexArray(m_VAO);
		m_VBO.push_back(0);
		glGenBuffers(1, &m_VBO.back());
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO.back());
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_data.vertices), m_data.vertices, GL_STATIC_DRAW);
	}
	std::vector<GLuint> m_VBO;
	GLuint m_VAO;
	Triangle m_data{};
	const char* m_vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"	ourColor = aColor;\n"
		"}\0";
	GLuint m_vertexShader;
};

class FragmentShader
{
public:
	FragmentShader()
	{
		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fragmentShader, 1, &m_fragmentShaderSource, nullptr);
	}
	~FragmentShader()
	{
		glDeleteShader(m_fragmentShader);
	}
	GLuint m_fragmentShader;
	const char* m_fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor,1.0);\n"
		"}\n\0";
};

class ShaderProgram
{
public:
	ShaderProgram(FragmentShader* fragmentShader, VertexShader* vertexShader)
		: m_fragmentShader{fragmentShader}, m_vertexShader{vertexShader}
	{
		m_shaderProgram = glCreateProgram();

		glAttachShader(m_shaderProgram, m_vertexShader->m_vertexShader);
		glAttachShader(m_shaderProgram, m_fragmentShader->m_fragmentShader);

		glLinkProgram(m_shaderProgram);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
	}
	void use()
	{
				glUseProgram(m_shaderProgram);
	}
	GLuint m_shaderProgram;
	FragmentShader* m_fragmentShader;
	VertexShader* m_vertexShader;
};

class Window
{
public:
	Window(int startingX=0, int startingY=0, int width=800, int height=600)
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
	~Window()
	{
		glfwTerminate();
	}
	//getters
	int get_startingX() const { return m_startingX; }
	int get_startingY() const { return m_startingY; }
	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
	GLFWwindow* get_windowPtr() const { return m_windowPtr; }
	//functions
	static float get_rand()
	{
		std::random_device rd{};
		std::mt19937 rand{ rd() };
		std::uniform_real_distribution<float> dist{ 0.f,1.f };

		return dist(rand);
	}
	static void load_gl()
	{
		gladLoadGLLoader((reinterpret_cast<GLADloadproc>(glfwGetProcAddress)));
	}

	void set_viewport()
	{
		glViewport(m_startingX, m_startingY, m_width, m_height);
	}

	void update(ShaderProgram* shaderProgram, VertexShader* vertexShader)
	{
		glfwGetWindowSize(m_windowPtr,&m_width, &m_height);
		glClear(GL_COLOR_BUFFER_BIT);
		render_triangle(shaderProgram, vertexShader);
		glfwSwapBuffers(m_windowPtr);
		glfwPollEvents();
	}

	static void render_triangle (ShaderProgram* shaderProgram, VertexShader* vertexShader)
	{
		glUseProgram(shaderProgram->m_shaderProgram);
		glBindVertexArray(vertexShader->m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void set_key_callback(void(*f)(GLFWwindow* win,int key, int scancode, int action, int mods))
	{
		glfwSetKeyCallback(m_windowPtr, f);
	}

private:
	int m_startingX{};
	int m_startingY{};
	int m_width{};
	int m_height{};
	static float m_verticesColor[9];
	GLFWwindow* m_windowPtr{};
	GLuint m_vao{};
};

float Window::m_verticesColor[] = { 1.f,0.f,0.f,
									0.f,1.f,0.f,
									0.f,0.f,1.f };

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
			case GLFW_KEY_SPACE:
				{
					if (action == GLFW_PRESS)
					{
						glClearColor(Window::get_rand(), Window::get_rand(), Window::get_rand(), 1.f);
					}
					break;
				}
			}
		});

	Triangle triangle{};
	VertexShader vertexShader{triangle};
	FragmentShader fragmentShader{};
	ShaderProgram shaderProgram{&fragmentShader, &vertexShader};

	while (!glfwWindowShouldClose(window.get_windowPtr()))
	{
		window.update(&shaderProgram, &vertexShader);
	}

	return 0;
}