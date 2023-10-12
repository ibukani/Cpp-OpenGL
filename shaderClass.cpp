#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) 
{

	// get shader code file
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// 頂点を表示するためのシェーダを作成
	// モデルが有る座標の情報から画面に映るためにどうすればいいかの計算命令が
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// シェーダーの中身を設定
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	// シェーダーをコンパイル
	glCompileShader(vertexShader);

	// 色を決定するためのシェーダーを作成
	// 様々な情報（例えば光）をもとにしてその部分に正しい色を割り当てるためのシェーダ
	GLuint fragmentShander = glCreateShader(GL_FRAGMENT_SHADER);
	// シェーダーの中身を設定
	glShaderSource(fragmentShander, 1, &fragmentSource, nullptr);
	// シェーダーをコンパイル
	glCompileShader(fragmentShander);

	// 上のシェーダーをまとめるためのプログラムを作成
	ID = glCreateProgram();
	// シェーダーを付与
	glAttachShader(ID, fragmentShander);
	glAttachShader(ID, vertexShader);
	// 付与して使える状態にするためのリンク
	glLinkProgram(ID);

	// シェーダーの削除
	glDeleteShader(fragmentShander);
	glDeleteShader(vertexShader);

}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}