#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	// 生成
	glGenBuffers(1, &ID);
	// バインド
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// 詳細をアップロード
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() 
{
	// IDにArrayBufferをバインドする
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::UnBind()
{
	// VAOとVBOをバインドして誤って変な情報を入力されないようにする
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}