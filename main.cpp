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
	// GLFWの初期化
	glfwInit();

	// OpenGLの設定
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// 頂点のデータ
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

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

	// 頂点を表示するためのシェーダを作成
	// モデルが有る座標の情報から画面に映るためにどうすればいいかの計算命令が
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// シェーダーの中身を設定
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// シェーダーをコンパイル
	glCompileShader(vertexShader);

	// 色を決定するためのシェーダーを作成
	// 様々な情報（例えば光）をもとにしてその部分に正しい色を割り当てるためのシェーダ
	GLuint fragmentShander = glCreateShader(GL_FRAGMENT_SHADER);
	// シェーダーの中身を設定
	glShaderSource(fragmentShander, 1, &fragmentShaderSource, NULL);
	// シェーダーをコンパイル
	glCompileShader(fragmentShander);

	// 上のシェーダーをまとめるためのプログラムを作成
	GLuint shaderProgram = glCreateProgram();
	// シェーダーを付与
	glAttachShader(shaderProgram, fragmentShander);
	glAttachShader(shaderProgram, vertexShader);
	// 付与して使える状態にするためのリンク
	glLinkProgram(shaderProgram);

	// シェーダーの削除
	glDeleteShader(fragmentShander);
	glDeleteShader(vertexShader);


	// VBO　ー＞　頂点や色のデータを一時的に保存しておく場所
	// VBO: Vertex Beffer Object
	// VAO -> 頂点のデータや属性などを保持して置く場所
	// VAO: Vertex Array Object
	// VAOとVBOの違い　-> VBOはGPUに受け渡すための容器、VAOは頂点データを設定して有効化する
	GLuint VAO, VBO;

	// Bufferと Arrayの作成
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// VAOにVertexArrayを付与
	glBindVertexArray(VAO);
	
	// VBOにARRAYのバッファーであることを付与
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 中身を設定
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// VertexArrayの属性を設定
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 属性を有効にする
	glEnableVertexAttribArray(0);

	// VAOとVBOをバインドして誤って変な情報を入力されないようにする
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Backgroundのカラー設定
	glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
	// バックグラウンドのカラーを削除
	glClear(GL_COLOR_BUFFER_BIT);
	// バッファーを入れ替える
	glfwSwapBuffers(window);

	// WindowのCloseを検知してそれまでループさせる
	while (!glfwWindowShouldClose(window))
	{
		// Backgroundのカラー設定
		glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
		// バックグラウンドのカラーを削除
		glClear(GL_COLOR_BUFFER_BIT);
		// 上で設定したプログラムを使用するように（アクティブにする）
		glUseProgram(shaderProgram);
		// VAOを指定して、そのデータを有効化する
		glBindVertexArray(VAO);
		// 頂点を描画する
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// バッファーを入れ替える
		glfwSwapBuffers(window);

		// マウスやキーボードなどのイベントを記録する
		glfwPollEvents();
	}

	// いままで設定してきた値を消去
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteShader(shaderProgram);

	// Windowを消去
	glfwDestroyWindow(window);
	// glfwを終了する
	glfwTerminate();
	return 0;
}
