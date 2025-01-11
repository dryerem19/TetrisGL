#include "Shader.h"

#include <algorithm> // std::copy
#include <iterator>  // std::ostream_iterator
#include <iostream>  // std::cout

Shader::Shader()
{
    _shaders.reserve(2);
}

Shader::~Shader()
{
    this->DeleteShaders();

    if (_programId) {
        glDeleteProgram(_programId);
    }
}

bool Shader::Create()
{
    GLuint program = this->CreateProgram(_shaders.data(), _shaders.size());

    bool result = program && this->CheckProgramLinking(program);
    if (result) {
        _programId = program;
        _isLinked = true;
    }

    this->DeleteShaders();
    return result;
}

bool Shader::AddShaderFromSourceCode(ShaderType type, const std::string& source)
{
    const char* raw = source.c_str();
    return this->AddShaderFromSourceCode(type, raw);
}

bool Shader::AddShaderFromSourceCode(ShaderType type, const char* source)
{
    GLuint shader = this->CompileShader(static_cast<GLenum>(type), source);
    
    bool result = shader && this->CheckShaderCompilation(shader);
    if (result) {
        _shaders.push_back(shader);
    }
    else {
        std::cout << source << std::endl;
    }

    return result;
}

int Shader::AttributeLocation(const std::string& name) const
{
    return this->AttributeLocation(name.c_str());
}

int Shader::AttributeLocation(const char* name) const
{
    int result = glGetUniformLocation(_programId, name);
    
    if (result == -1) {
        std::cout << "Cannot found uniform location: " << name << std::endl;
    }

    return result;
}

GLuint Shader::ProgramId() const
{
    return _programId;
}

bool Shader::IsLinked() const
{
    return _isLinked;
}

void Shader::DeleteShaders()
{
    for (const auto& shader : _shaders) {
        if (shader) {
            glDeleteShader(shader);
        }
    }

    _shaders.clear();
}

GLuint Shader::CompileShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    return shader;
}

GLuint Shader::CreateProgram(GLuint* shaders, int size)
{
    GLuint program = glCreateProgram();
    
    for (int i = 0; i < size; ++i) {
        glAttachShader(program, *(shaders + i));
    }

    glLinkProgram(program);
    return program;
}

GLint Shader::CheckShaderCompilation(GLuint shader)
{
    GLint success{ GL_FALSE };
    GLint logLength{ 512 };

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            std::vector<char> infoLog(logLength);
            glGetShaderInfoLog(shader, logLength, nullptr, infoLog.data());

            /* Сообщаем об ошибке */
            std::cout << "ERROR::SHADER::COMPILATION_FAILED:" << std::endl;

            /* Печатаем текст лога, просто копируя вектор в выходной поток */
            std::copy(infoLog.begin(), infoLog.end(), std::ostream_iterator<char>(std::cout));

            /* Завершаем строку */
            std::cout << std::endl;
        }
    }

    return success;
}

GLint Shader::CheckProgramLinking(GLuint program)
{
    GLint success{ GL_FALSE };
    GLint logLength{ 512 };

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            std::vector<char> infoLog(logLength);
            glGetProgramInfoLog(program, logLength, nullptr, infoLog.data());

            /* Сообщаем об ошибке */
            std::cout << "ERROR::SHADER::PROGRAM_LINKING_FAILED" << std::endl;

            /* Печатаем текст лога, просто копируя вектор в выходной поток */
            std::copy(infoLog.begin(), infoLog.end(), std::ostream_iterator<char>(std::cout));

            /* Завершаем строку */
            std::cout << std::endl;
        }
    }

    return success;
}
