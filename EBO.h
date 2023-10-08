#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

// EBO: 頂点の重複を避けるために最適化を行う
// index bufferの話
class EBO
{
	public:
		GLuint ID;
		EBO(GLuint* indices, GLsizeiptr size);

		void Bind();
		void UnBind();
		void Delete();
};

#endif // !EBO_CLASS_H
#pragma once
