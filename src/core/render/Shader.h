#pragma once

#include <vector>    // std::vector
#include <string>    // std::string

#include <glad/glad.h>

/*
* @brief ��������� ��������� � ������������ ��������� �������� OpenGL.
*/
class Shader
{
public:

	/**
	* @brief ������������ ��������� ����� �������.
	*/
	enum class ShaderType
	{
		Vertex   = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};

	/*
	* @brief ����������� �� ���������.
	*/
	Shader();

	/*
	* @brief ����������.
	*/
	~Shader();

	/**
	* @brief ������ ��������� ���������.
	* 
	* @return ���� ��������� ���� ������� ������� True, ����� False.
	*/
	bool Create();

	/*
	* @brief ����������� ������ ���������� ����.
	* 
	* ��� ������� ������������� ��� �������� ���������� �������� � ��������� ���������.
	* 
	* @param type ��� �������.
	* @param source �������� ��� �������.
	* 
	* @return ���������� true, ���� ���������� ������ �������, ����� false.
	*/
	bool AddShaderFromSourceCode(ShaderType type, const std::string& source);
	
	/*
	* @brief ��� ������������� �������.
	*
	* ����������� ������ ���������� ����.
	* ��� ������� ������������� ��� �������� ���������� �������� � ��������� ���������.
	*
	* @param type ��� �������.
	* @param source �������� ��� �������.
	*
	* @return ���������� true, ���� ���������� ������ �������, ����� false.
	*/
	bool AddShaderFromSourceCode(ShaderType type, const char* source);

	/*
	* @brief ���������� �������������� �������� � ������ ���������� ���� ��������� ���������.
	* 
	* @param name ��� ��������.
	* 
	* @return ���������� -1, ���� ��� �� �������� ����������.
	*/
	int AttributeLocation(const std::string& name) const;

	/*
	* @brief ��� ������������� �������.
	*
	* ���������� �������������� �������� � ������ ���������� ���� ��������� ���������
	* 
	* @param name ��� ��������.
	*
	* @return ���������� -1, ���� ��� �� �������� ����������.
	*/
	int AttributeLocation(const char* name) const;

	/*
	* @brief ���������� ������������� ��������� ���������.
	*/
	GLuint ProgramId() const;

	/**
	* @brief ���������� true, ���� ��� ��������� ��������� �������, ����� false.
	*/
	bool IsLinked() const;

private:

	/**
	* @brief ������ ��������, ������� ����� ���������� � ��������� ��������� ����� ������ /ref Create()
	*/
	std::vector<GLuint> _shaders;

	/*
	* @brief ���� �� ��� ��������� ��������� �������.
	*/
	bool _isLinked{ false };

	/**
	* @brief ������������� ��������� ���������.
	*/
	GLuint _programId{ 0 };

	/**
	* @brief ������� ����� ��������� �������.
	*/
	void DeleteShaders();

	/**
	* @brief ������ � ����������� ������.
	* 
	* @param shaderType ��� �������.
	* @param shaderSource �������� ��� �������.
	* 
	* @return ������������� ���������� �������.
	*/
	GLuint CompileShader(GLenum shaderType, const char* shaderSource);
	
	/**
	* @brief ������ ��������� ���������.
	* 
	* @param shaders ��������� �� ������ ��������.
	* @param size ���������� ��������.
	* 
	* @return ������������� ��������� ��������� ���������.
	*/
	GLuint CreateProgram(GLuint* shaders, int size);
	
	/**
	* @brief ��������� ��������� ���������� �������. 
	* 
	* @param shader ������ �������.
	* 
	* @return ���������� GL_TRUE, ���� ���������� ������ �������, ����� GL_FALSE.
	*/
	GLint CheckShaderCompilation(GLuint shader);

	/**
	* @brief ��������� ��������� �������� �������.
	* 
	* @param program ������ ��������� ���������.
	* 
	* @return ���������� GL_TRUE, ���� �������� ������ �������, ����� GL_FALSE.
	*/
	GLint CheckProgramLinking(GLuint program);
};