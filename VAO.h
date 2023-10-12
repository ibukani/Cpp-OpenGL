#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

// VAO -> 頂点のデータや属性などを保持して置く場所
// VAO: Vertex Array Object
// VAOとVBOの違い　-> VBOはGPUに受け渡すための容器、VAOは頂点データを設定して有効化する
class VAO
{
	public:
		GLuint ID;
		VAO();

		void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void UnBind();
		void Delete();
};

#endif // !VAO_CLASS_H
