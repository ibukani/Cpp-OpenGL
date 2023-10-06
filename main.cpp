#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main(void)
{
	// GLFW�̏�����
	glfwInit();

	// OpenGL�̐ݒ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// ���_�̃f�[�^
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

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

	// ���_��\�����邽�߂̃V�F�[�_���쐬
	// ���f�����L����W�̏�񂩂��ʂɉf�邽�߂ɂǂ�����΂������̌v�Z���߂�
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// �V�F�[�_�[�̒��g��ݒ�
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// �V�F�[�_�[���R���p�C��
	glCompileShader(vertexShader);

	// �F�����肷�邽�߂̃V�F�[�_�[���쐬
	// �l�X�ȏ��i�Ⴆ�Ό��j�����Ƃɂ��Ă��̕����ɐ������F�����蓖�Ă邽�߂̃V�F�[�_
	GLuint fragmentShander = glCreateShader(GL_FRAGMENT_SHADER);
	// �V�F�[�_�[�̒��g��ݒ�
	glShaderSource(fragmentShander, 1, &fragmentShaderSource, NULL);
	// �V�F�[�_�[���R���p�C��
	glCompileShader(fragmentShander);

	// ��̃V�F�[�_�[���܂Ƃ߂邽�߂̃v���O�������쐬
	GLuint shaderProgram = glCreateProgram();
	// �V�F�[�_�[��t�^
	glAttachShader(shaderProgram, fragmentShander);
	glAttachShader(shaderProgram, vertexShader);
	// �t�^���Ďg�����Ԃɂ��邽�߂̃����N
	glLinkProgram(shaderProgram);

	// �V�F�[�_�[�̍폜
	glDeleteShader(fragmentShander);
	glDeleteShader(vertexShader);


	// VBO�@�[���@���_��F�̃f�[�^���ꎞ�I�ɕۑ����Ă����ꏊ
	// VBO: Vertex Beffer Object
	// VAO -> ���_�̃f�[�^�⑮���Ȃǂ�ێ����Ēu���ꏊ
	// VAO: Vertex Array Object
	// VAO��VBO�̈Ⴂ�@-> VBO��GPU�Ɏ󂯓n�����߂̗e��AVAO�͒��_�f�[�^��ݒ肵�ėL��������
	GLuint VAO, VBO;

	// Buffer�� Array�̍쐬
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// VAO��VertexArray��t�^
	glBindVertexArray(VAO);
	
	// VBO��ARRAY�̃o�b�t�@�[�ł��邱�Ƃ�t�^
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���g��ݒ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// VertexArray�̑�����ݒ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ������L���ɂ���
	glEnableVertexAttribArray(0);

	// VAO��VBO���o�C���h���Č���ĕςȏ�����͂���Ȃ��悤�ɂ���
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Background�̃J���[�ݒ�
	glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
	// �o�b�N�O���E���h�̃J���[���폜
	glClear(GL_COLOR_BUFFER_BIT);
	// �o�b�t�@�[�����ւ���
	glfwSwapBuffers(window);

	// Window��Close�����m���Ă���܂Ń��[�v������
	while (!glfwWindowShouldClose(window))
	{
		// Background�̃J���[�ݒ�
		glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
		// �o�b�N�O���E���h�̃J���[���폜
		glClear(GL_COLOR_BUFFER_BIT);
		// ��Őݒ肵���v���O�������g�p����悤�Ɂi�A�N�e�B�u�ɂ���j
		glUseProgram(shaderProgram);
		// VAO���w�肵�āA���̃f�[�^��L��������
		glBindVertexArray(VAO);
		// ���_��`�悷��
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// �o�b�t�@�[�����ւ���
		glfwSwapBuffers(window);

		// �}�E�X��L�[�{�[�h�Ȃǂ̃C�x���g���L�^����
		glfwPollEvents();
	}

	// ���܂܂Őݒ肵�Ă����l������
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteShader(shaderProgram);

	// Window������
	glfwDestroyWindow(window);
	// glfw���I������
	glfwTerminate();
	return 0;
}
