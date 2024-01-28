#pragma once
#include <string_view>
#include <glad.h>
class Shader
{public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void set_bool(std::string_view name, bool value) const;
	void set_int(std::string_view name, int value) const;
	void set_float(std::string_view name, float value) const;
    unsigned int get_program_id() const;
private:
	unsigned int m_id{};
	static std::string read_shader(const char* shaderPath);
	static GLuint compile_shader(const char* shaderSource, GLenum shaderType);
	void linkProgram(GLuint vertexShader, GLuint fragmentShader);
};

