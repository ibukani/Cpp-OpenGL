#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// VAO‚ğAttribute‚ÉÚ‘±‚·‚é
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// VertexArray‚Ì‘®«‚ğİ’è
	glVertexAttribPointer(layout, numComponents, type, GL_FLOAT, stride, offset);
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