#pragma once

#include <string>
#include <unordered_map>
#include "BasicIncludes.h"

enum ShaderType
{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
private:
    unsigned int m_rendererID;
    std::string m_filePath;
    std::unordered_map<std::string, int> m_uniformLocation;

public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
    void SetUniform4x4(const std::string& name, glm::mat4 viewProj);
    void SetUniform1f(const std::string& name, float value);

private:
    int GetUniformLocation(const std::string& name);
    struct ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};