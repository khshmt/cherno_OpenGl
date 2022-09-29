#include <renderer.hpp>
#include <vertexBuffer.hpp>
#include <indexBuffer.hpp>
#include <GLFW/glfw3.h>
#include <vertexArray.hpp>
#include <shader.hpp>

const GLint WIDTH = 600, HEIGHT = 600;
const std::string filePath = "../res/shaders/basic.shader";


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
	//vertex array object;
	VertexArray va;
	//vertex buffer
	VertexBuffer vertexBuffer{verteciesPositions, 4*2*sizeof(float)}; 

	VertexBufferLayout layout;
	layout.push(2);
	va.addBuffer(vertexBuffer, layout);
	//index buffer
	IndexBuffer indexBuffer{indicies, 6};

	
	Shader shader(filePath);
	shader.Bind();
	shader.setUniform4f("u_Color", 0.9f, 0.3f, 0.8f, 1.0f);

	//clearing everthing befpore entering the rendering loop 
	//to be able to render more than one object in more than one program
	GLCall(va.unBind());
	shader.unBind();
    vertexBuffer.Unbind();
	indexBuffer.Unbind();

	float r=0.0, g=0.0, b=0.0;
	while(!glfwWindowShouldClose(mainWindow)) {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		shader.Bind(); //choose the program 
		shader.setUniform4f("u_Color", r, g, b, 1.0f);
		
		va.Bind(); //bind the vertex array object
		indexBuffer.Bind();
		
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

	GLCall(glfwTerminate());
	return 0;
}
