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
	// VertexShaderのコンパイルが失敗したときにエラーを出力する
	compileErrors(vertexShader, "VERTEX");

	// 色を決定するためのシェーダーを作成
	// 様々な情報（例えば光）をもとにしてその部分に正しい色を割り当てるためのシェーダ
	GLuint fragmentShander = glCreateShader(GL_FRAGMENT_SHADER);
	// シェーダーの中身を設定
	glShaderSource(fragmentShander, 1, &fragmentSource, nullptr);
	// シェーダーをコンパイル
	glCompileShader(fragmentShander);
	// FragmentShaderのコンパイルが失敗したときにエラーを出力する
	compileErrors(fragmentShander, "FRAGMENT");

	// 上のシェーダーをまとめるためのプログラムを作成
	ID = glCreateProgram();
	// シェーダーを付与
	glAttachShader(ID, fragmentShander);
	glAttachShader(ID, vertexShader);
	// 付与して使える状態にするためのリンク
	glLinkProgram(ID);
	// Programのリンクが失敗したときにエラーを出力する
	compileErrors(ID, "PROGRAM");

	// シェーダーの削除
	glDeleteShader(fragmentShander);
	glDeleteShader(vertexShader);

}

void Shader::Activate() 
{
	glUseProgram(ID);
}

void Shader::Delete() 
{
	glDeleteProgram(ID);
}

// シェーダーのコンパイルに失敗したときLOGをはくように
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}