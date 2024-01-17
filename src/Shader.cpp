#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	GLuint vertex{ compile_shader(read_shader(vertexPath).c_str(),GL_VERTEX_SHADER) };
	GLuint fragment{ compile_shader(read_shader(fragmentPath).c_str(),GL_FRAGMENT_SHADER) };
	linkProgram(vertex, fragment);

}

std::string Shader::read_shader(const char* shaderPath)
{
	std::string shaderCode;

	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
        size_t pos = 0;
        while ((pos = shaderCode.find('\r', pos)) != std::string::npos) {
            shaderCode.replace(pos, 1, "\n");
            pos += 1;  // Move past the replaced character
        }
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << std::endl;
	}
	return shaderCode;
}

GLuint Shader::compile_shader(const char* shaderSource, GLenum shaderType)
{
	GLuint shader;
	GLint success;
	char infoLog[512]{};

	shader = glCreateShader(shaderType);

	glShaderSource(shader,1,&shaderSource,nullptr);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLint success;
	char infoLog[512]{};

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);

	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(m_id);
}

void Shader::set_bool(std::string_view name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.data()), static_cast<int>(value));
}

void Shader::set_int(std::string_view name, int value) const
{
	glUniform1i(glGetUniformLocation(m_id, name.data()), value);
}

void Shader::set_float(std::string_view name, float value) const
{
	glUniform1f(glGetUniformLocation(m_id, name.data()), value);
}

unsigned int Shader::get_program_id() const {
    return m_id;
}




