#pragma once
#include <string>
#include "Dep/glm/glm.hpp"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Dep/glm/gtc/type_ptr.hpp"
#include <unordered_map>
class Shader
{
public:
	Shader() = default;
	Shader(std::string& VSPath, std::string& FSPath);
	void useShader();
    void destroyShader();
	void setUniformMat4f(std::string name , glm::mat4x4 mat);
	int getUniformLocation(const std::string& name);
	void setUniform1i(std::string name, int value);
private:
	std::string loadShaderSource(std::string& path);
	int compileShader(std::string& VSPath, std::string& FSPath);
	std::unordered_map<std::string, int> uniformLocationCache;
	int programID;
};

