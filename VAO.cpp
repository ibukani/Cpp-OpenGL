#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	// VertexArray‚Ì‘®«‚ğİ’è
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// ‘®«‚ğ—LŒø‚É‚·‚é
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
	// ‚¢‚Ü‚Ü‚Åİ’è‚µ‚Ä‚«‚½’l‚ğÁ‹
	glDeleteVertexArrays(1, &ID);
}