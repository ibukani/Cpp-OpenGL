#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

// VBO�@�[���@���_��F�̃f�[�^���ꎞ�I�ɕۑ����Ă����ꏊ
// VBO: Vertex Beffer Object
// VAO��VBO�̈Ⴂ�@-> VBO��GPU�Ɏ󂯓n�����߂̗e��AVAO�͒��_�f�[�^��ݒ肵�ėL��������
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
