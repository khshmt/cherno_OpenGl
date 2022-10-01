#include <debugger.hpp>
#include <renderer.hpp>

void Renderer::clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
	shader.Bind(); // choose the program
	va.Bind();	   // bind the vertex array object
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}