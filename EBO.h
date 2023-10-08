#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

// EBO: ���_�̏d��������邽�߂ɍœK�����s��
// index buffer�̘b
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
