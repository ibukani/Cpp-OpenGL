#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// VAO��Attribute�ɐڑ�����
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// VertexArray�̑�����ݒ�
	glVertexAttribPointer(layout, numComponents, type, GL_FLOAT, stride, offset);
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