#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// ���_�̃f�[�^
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // ���̊p
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // �E�̊p
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // ��ԏ�
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // �^�񒆂̍�
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // �^�񒆂̉E
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // �^�񒆂̉�

};

// �C���f�b�N�X�̃f�[�^
GLuint indices[] =
{
	0, 3, 5,
	3, 2, 4,
	5, 4, 1,
};

int main(void)
{
	// GLFW�̏�����
	glfwInit();

	// OpenGL�̐ݒ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window�̍쐬
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	// Window���쐬�Ɏ��s������A�Ȃ����LOG��\�������ăA�v�����I������B
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}
	// �R���e�L�X�g�� window �����ށB
	glfwMakeContextCurrent(window);

	// OpenGL��ǂݍ���
	gladLoadGL();

	// Viewport�̐ݒ�
	glViewport(0,0,800,800);

	// Shader�̍쐬
	Shader shaderProgram("default.vert", "default.flag");

	// VertexArray�̍쐬
	VAO VAO1;
	VAO1.Bind();

	// VertexBuffer �̍쐬
	VBO VBO1(vertices, sizeof(vertices));
	// ElementBuffer �̍쐬
	EBO EBO1(indices, sizeof(indices));

	// VBO�Ƃ̃����N
	VAO1.LinkVBO(VBO1, 0);

	// UnBIND�̏���
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();


	// Window��Close�����m���Ă���܂Ń��[�v������
	while (!glfwWindowShouldClose(window))
	{
		// Background�̃J���[�ݒ�
		glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
		// �o�b�N�O���E���h�̃J���[���폜
		glClear(GL_COLOR_BUFFER_BIT);
		// ��Őݒ肵���v���O�������g�p����悤�Ɂi�A�N�e�B�u�ɂ���j
		shaderProgram.Activate();
		// VAO���w�肵�āA���̃f�[�^��L��������
		VAO1.Bind();
		// ���_��`�悷��
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// �o�b�t�@�[�����ւ���
		glfwSwapBuffers(window);

		// �}�E�X��L�[�{�[�h�Ȃǂ̃C�x���g���L�^����
		glfwPollEvents();
	}

	// Delete Buffer & Shaders
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Window������
	glfwDestroyWindow(window);
	// glfw���I������
	glfwTerminate();
	return 0;
}
