#include "Shader.h"


Shader::Shader(std::string& VSPath, std::string& FSPath)
{
	this->programID = compileShader(VSPath, FSPath);
}

int Shader::compileShader(std::string& VSPath, std::string& FSPath)
{
	int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string vertexShaderSource = loadShaderSource(VSPath), fragmentShaderSource = loadShaderSource(FSPath);
	const char* VSSource = vertexShaderSource.c_str(), * FSSource = fragmentShaderSource.c_str();

	glShaderSource(vertexShaderID, 1, &VSSource, nullptr);
	glCompileShader(vertexShaderID);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glShaderSource(fragmentShaderID, 1, &FSSource, nullptr);
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	int programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

std::string Shader::loadShaderSource(std::string& path)
{
	std::ifstream stream(path);
	std::string line;
	std::stringstream ss;
	while (getline(stream, line))
	{
		ss << line << '\n';
	}
	std::string source = ss.str();
	return source;
}

void Shader::useShader()
{
	glUseProgram(this->programID);
}

void Shader::destroyShader()
{
	glDeleteProgram(this->programID);
}

void Shader::setUniformMat4f(std::string name, glm::mat4x4 mat)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

int Shader::getUniformLocation(const std::string& name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
	{
		return uniformLocationCache[name];
	}
	int location = glGetUniformLocation(programID, name.c_str());
	if (location == -1)
		std::cout << "Uniform " << name << " does not exist!\n";
	uniformLocationCache[name] = location;
	return location;
}

void Shader::setUniform1i(std::string name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}
