#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// 頂点のデータ
GLfloat vertices[] =
{
	-0.5f,  -0.5f, 0.0f,   1.0f, 0.0f,  0.0f,  // 左の角
	-0.5f,   0.5f, 0.0f,   0.0f, 1.0f,  0.0f,  // 右の角
	 0.5f,   0.5f, 0.0f,   0.0f, 0.0f,  1.0f,  // 一番上
	 0.5f,  -0.5f, 0.0f,   1.0f, 1.0f,  1.0f,  // 真ん中の左
};

// インデックスのデータ
GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2,
};

int main(void)
{
	// GLFWの初期化
	glfwInit();

	// OpenGLの設定
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Windowの作成
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	// Windowが作成に失敗したら、なければLOGを表示させてアプリを終了する。
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}
	// コンテキストに window を込む。
	glfwMakeContextCurrent(window);

	// OpenGLを読み込む
	gladLoadGL();

	// Viewportの設定
	glViewport(0,0,800,800);

	// Shaderの作成
	Shader shaderProgram("default.vert", "default.flag");

	// VertexArrayの作成
	VAO VAO1;
	VAO1.Bind();

	// VertexBuffer の作成
	VBO VBO1(vertices, sizeof(vertices));
	// ElementBuffer の作成
	EBO EBO1(indices, sizeof(indices));

	// VBOとのリンク
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// UnBINDの処理
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();


	GLuint  uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// WindowのCloseを検知してそれまでループさせる
	while (!glfwWindowShouldClose(window))
	{
		// Backgroundのカラー設定
		glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
		// バックグラウンドのカラーを削除
		glClear(GL_COLOR_BUFFER_BIT);
		// 上で設定したプログラムを使用するように（アクティブにする）
		shaderProgram.Activate();
		// scaleのあったいを0.5fに変更
		glUniform1f(uniID, 0.5f);
		// VAOを指定して、そのデータを有効化する
		VAO1.Bind();
		// 頂点を描画する
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// バッファーを入れ替える
		glfwSwapBuffers(window);

		// マウスやキーボードなどのイベントを記録する
		glfwPollEvents();
	}

	// Delete Buffer & Shaders
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Windowを消去
	glfwDestroyWindow(window);
	// glfwを終了する
	glfwTerminate();
	return 0;
}
