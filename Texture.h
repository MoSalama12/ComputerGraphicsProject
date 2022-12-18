#pragma once
#include "stb_image.h"
#include "Dep/include/glad/glad.h"
#include <iostream>
class Texture
{
public:
	Texture() = default;
	~Texture();
	Texture(std::string filepath);
	int getWidth() { return width; }
	int getHeight() { return height; }
	void Bind(unsigned int slot = 0);
	void Unbind();
private:
	int width, height, numberOfChannels;
	std::string filepath;
	unsigned char* data;
	unsigned int texture;
};

