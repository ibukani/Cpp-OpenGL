#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	// VertexArray�̑�����ݒ�
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// ������L���ɂ���
	glEnableVertexAttribArray(layout);
	VBO.UnBind();
}

void VAO::Bind() 
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	// ���܂܂Őݒ肵�Ă����l������
	glDeleteVertexArrays(1, &ID);
}