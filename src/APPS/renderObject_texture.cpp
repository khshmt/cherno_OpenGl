#include <debugger.hpp>
#include <vertexBuffer.hpp>
#include <indexBuffer.hpp>
#include <GLFW/glfw3.h>
#include <vertexArray.hpp>
#include <shader.hpp>
#include <renderer.hpp>
#include <texture.hpp>

const GLint WIDTH = 600, HEIGHT = 600;
const std::string filePath = "../res/shaders/basic_texture.shader";
const std::string textureFilePath = "../res/imgs/16992087.png";


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

	float verteciesPositions[] = {-0.5f, -0.5f, 0.0, 0.0f, //0
								   0.5f, -0.5f, 1.0f, 0.0f, //1
								   0.5f, 0.5f,  1.0f, 1.0f,//2 
								  -0.5f, 0.5f, 0.0f, 1.0f}; //3
	unsigned int indicies[] = {0, 1, 2,  //triangle 1 
							   2, 3, 0}; // triangle 2
	//vertex array object;
	VertexArray va;
	//vertex buffer
	VertexBuffer vertexBuffer{verteciesPositions, 4*4*sizeof(float)}; 

	VertexBufferLayout layout;
	layout.push(2);
    layout.push(2);
	va.addBuffer(vertexBuffer, layout);
	//index buffer
	IndexBuffer indexBuffer{indicies, 6};

	
	Shader shader(filePath);
	shader.Bind();
    
    Texture texture(textureFilePath);
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);
	//clearing everthing befpore entering the rendering loop 
	//to be able to render more than one object in more than one program
	GLCall(va.unBind());
	shader.unBind();
    vertexBuffer.Unbind();
	indexBuffer.Unbind();

	Renderer renderer;

	while(!glfwWindowShouldClose(mainWindow)) {
		renderer.clear();
		shader.Bind(); //choose the program 
		shader.setUniform1i("u_Texture", 0);		
		renderer.Draw(va, indexBuffer, shader);
		GLCall(glfwSwapBuffers(mainWindow));
		GLCall(glfwPollEvents());
	}

	GLCall(glfwTerminate());
	return 0;
}
