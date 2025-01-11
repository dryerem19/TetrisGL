#pragma once

#include <vector>    // std::vector
#include <string>    // std::string

#include <glad/glad.h>

/*
* @brief Позволяет связывать и использовать программы шейдеров OpenGL.
*/
class Shader
{
public:

	/**
	* @brief Перечисление возможных типов шейдера.
	*/
	enum class ShaderType
	{
		Vertex   = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};

	/*
	* @brief Конструктор по умолчанию.
	*/
	Shader();

	/*
	* @brief Деструктор.
	*/
	~Shader();

	/**
	* @brief Создаёт шейдерную программу.
	* 
	* @return Если программа была успешно создана True, иначе False.
	*/
	bool Create();

	/*
	* @brief Компилирует шейдер указанного типа.
	* 
	* Эта функция предназначена для быстрого добавления шейдеров в шейдерную программу.
	* 
	* @param type Тип шейдера.
	* @param source Исходный код шейдера.
	* 
	* @return Возвращает true, если компиляция прошла успешно, иначе false.
	*/
	bool AddShaderFromSourceCode(ShaderType type, const std::string& source);
	
	/*
	* @brief Это перегруженная функция.
	*
	* Компилирует шейдер указанного типа.
	* Эта функция предназначена для быстрого добавления шейдеров в шейдерную программу.
	*
	* @param type Тип шейдера.
	* @param source Исходный код шейдера.
	*
	* @return Возвращает true, если компиляция прошла успешно, иначе false.
	*/
	bool AddShaderFromSourceCode(ShaderType type, const char* source);

	/*
	* @brief Возвращает местоположение атрибута в списке параметров этой шейдерной программы.
	* 
	* @param name Имя атрибута.
	* 
	* @return Возвращает -1, если имя не является допустимым.
	*/
	int AttributeLocation(const std::string& name) const;

	/*
	* @brief Это перегруженная функция.
	*
	* Возвращает местоположение атрибута в списке параметров этой шейдерной программы
	* 
	* @param name Имя атрибута.
	*
	* @return Возвращает -1, если имя не является допустимым.
	*/
	int AttributeLocation(const char* name) const;

	/*
	* @brief Возвращает идентификатор шейдерной программы.
	*/
	GLuint ProgramId() const;

	/**
	* @brief Возвращает true, если эта шейдерная программа связана, иначе false.
	*/
	bool IsLinked() const;

private:

	/**
	* @brief Вектор шейдеров, которые будут слинкованы в шейдерную программу после вызова /ref Create()
	*/
	std::vector<GLuint> _shaders;

	/*
	* @brief Была ли эта шейдерная программа связана.
	*/
	bool _isLinked{ false };

	/**
	* @brief Идентификатор шейдерной программы.
	*/
	GLuint _programId{ 0 };

	/**
	* @brief Удаляет ранее созданный шейдеры.
	*/
	void DeleteShaders();

	/**
	* @brief Создаёт и компилирует шейдер.
	* 
	* @param shaderType Тип шейдера.
	* @param shaderSource Исходный код шейдера.
	* 
	* @return Идентификатор созданного шейдера.
	*/
	GLuint CompileShader(GLenum shaderType, const char* shaderSource);
	
	/**
	* @brief Создаёт шейдерную программу.
	* 
	* @param shaders Указатель на массив шейдеров.
	* @param size Количество шейдеров.
	* 
	* @return Идентификатор созданной шейдерной программы.
	*/
	GLuint CreateProgram(GLuint* shaders, int size);
	
	/**
	* @brief Проверяет результат компиляции шейдера. 
	* 
	* @param shader Объект шейдера.
	* 
	* @return Возвращает GL_TRUE, если компиляция прошла успешно, иначе GL_FALSE.
	*/
	GLint CheckShaderCompilation(GLuint shader);

	/**
	* @brief Проверяет результат линковки шейдера.
	* 
	* @param program Объект шейдерной программы.
	* 
	* @return Возвращает GL_TRUE, если линковка прошла успешно, иначе GL_FALSE.
	*/
	GLint CheckProgramLinking(GLuint program);
};