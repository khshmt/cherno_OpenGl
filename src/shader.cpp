#include <GL/glew.h>
#include <shader.hpp>

Shader::Shader(const std::string& filePath) : _filePath(filePath), _RendererId(0) {
    GLCall(auto shaders = parsesShader());
	GLCall(_RendererId = createShader(shaders.vertexShader, shaders.fragmentShader ));
}
Shader::~Shader() {
    GLCall(glDeleteProgram(_RendererId));
}
unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	GLint result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if(result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		
		char message[length];
		// char* message = (char*)alloca(length*sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "falied to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl; 
		std::cout << message << std::endl; 

		return 0;
		GLCall(glDeleteShader(id));
	}
	
	return id;
}
void Shader::Bind() const {
    GLCall(glUseProgram(_RendererId));
}
void Shader::unBind() {
    GLCall(glUseProgram(0));
}
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string& name, int value) {
	GLCall(glUniform1i(getUniformLocation(name), value));
}

int Shader::getUniformLocation(const std::string& name) {
    if(_uniformLocationCACHE.find(name) != _uniformLocationCACHE.end()) //caching procedure
        return _uniformLocationCACHE[name];
    GLCall(int location = glGetUniformLocation(_RendererId, name.c_str()));
    if(location == -1)
        std::cout << "warnning: uniform '" << name << "' doesn't exist\n";  
    _uniformLocationCACHE[name] = location;
    return location;
} 

ShaderProgramSources Shader::parsesShader() {
	std::ifstream stream(_filePath);

	enum class ShaderType {NONE=-1, VERTEX=0, FRAGMENT=1};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while(std::getline(stream, line)) {
		if(line.find("#shader") != std::string::npos) {
			if(line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if(line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		} else {
			ss[static_cast<int>(type)] << line << "\n";
		}
	}
	return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	GLCall(unsigned int program = glCreateProgram());
	GLCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader));
	GLCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader));
	
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}