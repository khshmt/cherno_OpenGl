#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <debugger.hpp>
#include <unordered_map>
struct ShaderProgramSources {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader {
private:
    unsigned int _RendererId;
    std::string _filePath;
    std::unordered_map<std::string, int> _uniformLocationCACHE;
public:
    Shader(const std::string& filePath);
    ~Shader();

    void Bind() const;
    void unBind();
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniform1i(const std::string& name, int value);

private:
    ShaderProgramSources parsesShader();
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    int getUniformLocation(const std::string& name);
    
};