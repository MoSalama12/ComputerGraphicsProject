#pragma once
#include <vector>
#include "Dep/include/glad/glad.h"
#include "Dep/include/GLFW/glfw3.h"

using namespace std;

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int normalized;
	unsigned int typeSize;
};

class VertexBufferLayout
{
	vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride; 
public:
	VertexBufferLayout();

	template<typename T>
	void push(unsigned int count);
	unsigned int GetStride() const;
	const vector<VertexBufferElement>& GetElements() const;

	~VertexBufferLayout();
};
