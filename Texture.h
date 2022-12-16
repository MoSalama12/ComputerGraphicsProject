#pragma once
#include "stb_image.h"
#include "Dep/include/glad/glad.h"
#include <iostream>
class Texture
{
public:
	Texture() = default;
	Texture(const char* src);
	void Bind();
private:
	int width, height, numberOfChannels;
	unsigned char* data;
	unsigned int texture;
};

