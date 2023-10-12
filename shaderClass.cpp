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

	// ���_��\�����邽�߂̃V�F�[�_���쐬
	// ���f�����L����W�̏�񂩂��ʂɉf�邽�߂ɂǂ�����΂������̌v�Z���߂�
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// �V�F�[�_�[�̒��g��ݒ�
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	// �V�F�[�_�[���R���p�C��
	glCompileShader(vertexShader);

	// �F�����肷�邽�߂̃V�F�[�_�[���쐬
	// �l�X�ȏ��i�Ⴆ�Ό��j�����Ƃɂ��Ă��̕����ɐ������F�����蓖�Ă邽�߂̃V�F�[�_
	GLuint fragmentShander = glCreateShader(GL_FRAGMENT_SHADER);
	// �V�F�[�_�[�̒��g��ݒ�
	glShaderSource(fragmentShander, 1, &fragmentSource, nullptr);
	// �V�F�[�_�[���R���p�C��
	glCompileShader(fragmentShander);

	// ��̃V�F�[�_�[���܂Ƃ߂邽�߂̃v���O�������쐬
	ID = glCreateProgram();
	// �V�F�[�_�[��t�^
	glAttachShader(ID, fragmentShander);
	glAttachShader(ID, vertexShader);
	// �t�^���Ďg�����Ԃɂ��邽�߂̃����N
	glLinkProgram(ID);

	// �V�F�[�_�[�̍폜
	glDeleteShader(fragmentShander);
	glDeleteShader(vertexShader);

}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}