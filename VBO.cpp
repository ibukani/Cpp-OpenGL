#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	// ����
	glGenBuffers(1, &ID);
	// �o�C���h
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// �ڍׂ��A�b�v���[�h
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() 
{
	// ID��ArrayBuffer���o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind()
{
	// VAO��VBO���o�C���h���Č���ĕςȏ�����͂���Ȃ��悤�ɂ���
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}