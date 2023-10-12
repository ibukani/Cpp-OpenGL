#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

// VAO -> ���_�̃f�[�^�⑮���Ȃǂ�ێ����Ēu���ꏊ
// VAO: Vertex Array Object
// VAO��VBO�̈Ⴂ�@-> VBO��GPU�Ɏ󂯓n�����߂̗e��AVAO�͒��_�f�[�^��ݒ肵�ėL��������
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
