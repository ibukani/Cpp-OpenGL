#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	// ID��ElementArrayBuffer���o�C���h����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// ���g�̐ݒ�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	// ID��ElementArrayBuffer���o�C���h����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind()
{
	// VAO��VBO���o�C���h���Č���ĕςȏ�����͂���Ȃ��悤�ɂ���
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}