#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

const GLint WIDTH = 600, HEIGHT = 600;
const std::string filePath = "../res/shaders/basic.shader";

#define GLCall(x) GlClearError();\
x;\
assert(GlLogCall(#x, __FILE__, __LINE__))

static void GlClearError() {
	while(glGetError() != GL_NO_ERROR); //GL_NO_ERROR = 0
}

static bool GlLogCall(const char* function, const char* file, int line) {
	auto error = glGetError();
	while(error) {
		std::cout << "[OpenGl Error] (" << error << ")"<< ": " << function << ": "
		<< file<< ": " << line << ": " << std::endl;
		return false;
	}
	return true;
}

struct ShaderProgramSources {
	std::string vertexShader;
	std::string fragmentShader;
};

static ShaderProgramSources parsesShader(const std::string& filePath) {
	std::ifstream stream(filePath);

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

static unsigned int compileShader(unsigned int type, const std::string& source) {
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

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

int main() {
	
	if(!glfwInit()) { 
		std::cout << "failed to initialize glfw !!\n";
		GLCall(glfwTerminate());
		return -1;
	}

	/*setup GLFW window properties*/
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3)); //determine version 3.3 version of opengl to use
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)); //core profile =  no backward compitability
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //allow forward compatability


	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "mainWindow", NULL, NULL);
	if(!mainWindow) {
		std::cout << "failed to create a window !!\n";
		GLCall(glfwTerminate());
		return -1;
	}
	GLCall(glfwMakeContextCurrent(mainWindow));
	GLCall(glfwSwapInterval(1));
	if(glewInit() != GLEW_OK) {
		std::cout << "failed to initialize glew\n";
		return -1;
	}
	std::cout << glGetString(GL_VERSION) << "\n";

	float verteciesPositions[] = {-0.5f, -0.5f, //0
								   0.5f, -0.5f, //1
								   0.5f, 0.5f,  //2 
								  -0.5f, 0.5f}; //3
	unsigned int indicies[] = {0, 1, 2,  //triangle 1 
							   2, 3, 0}; // triangle 2
	//vertex array object
	unsigned int vao{0}; 
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));
	
	//vertex buffer
	GLuint bufferId{0};
	GLCall(glGenBuffers(1, &bufferId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), verteciesPositions, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	//vertex buffer layout specification
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0)); 
	
	//index buffer
	GLuint ibo{0};
	GLCall(glGenBuffers(1, &ibo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indicies, GL_STATIC_DRAW));

	GLCall(auto shaders = parsesShader(filePath));
	GLCall(unsigned int program = createShader(shaders.vertexShader, shaders.fragmentShader ));
	GLCall(glUseProgram(program));

	GLCall(int location = glGetUniformLocation(program, "u_Color"));
	assert(location != -1);
	GLCall(glUniform4f(location, 0.9f, 0.3f, 0.8f, 1.0f));

	//clearing everthing befpore entering the rendering loop 
	//to be able to render more than one object in more than one program
	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	float r=0.0, g=0.0, b=0.0;
	while(!glfwWindowShouldClose(mainWindow)) {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glUseProgram(program)); //choose the program 
		GLCall(glUniform4f(location, r, g, b, 1.0f));
		
		GLCall(glBindVertexArray(vao)); //bind the vertex array object
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)); //bind index buffer
		
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // 6 is the number of indicies
		GLCall(glfwSwapBuffers(mainWindow));
		GLCall(glfwPollEvents());
		if(r>1.0f) {
			r = 0.0f; 
			g = 0.0f;
			b = 0.0f;
		} 
		r += 0.05f;
		g += 0.05f;
		b += 0.05f;
	}

	GLCall(glDeleteProgram(program));
	GLCall(glfwTerminate());
	return 0;
}
