#pragma once
#include <string>
#include "Dep/glm/glm.hpp"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Dep/glm/gtc/type_ptr.hpp"
class Shader
{
public:
	Shader() = default;
	Shader(std::string& VSPath, std::string& FSPath);
	void useShader();
    void destroyShader();
	void uniformMat4x4(const char* uniformName, glm::mat4x4 mat);
private:
	int compileShader(std::string& VSPath, std::string& FSPath);
	std::string loadShaderSource(std::string& path);
	int programID;
};

