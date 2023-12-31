#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// VAOをAttributeに接続する
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// VertexArrayの属性を設定
	glVertexAttribPointer(layout, numComponents, type, GL_FLOAT, stride, offset);
	// 属性を有効にする
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
	// いままで設定してきた値を消去
	glDeleteVertexArrays(1, &ID);
}