#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

// VBO　ー＞　頂点や色のデータを一時的に保存しておく場所
// VBO: Vertex Beffer Object
// VAOとVBOの違い　-> VBOはGPUに受け渡すための容器、VAOは頂点データを設定して有効化する
class VBO
{
	public:
		GLuint ID;
		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void UnBind();
		void Delete();
};

#endif // !VBO_CLASS_H
