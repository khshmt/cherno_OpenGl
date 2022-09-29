#include <indexBuffer.hpp>
#include <renderer.hpp>
#include <assert.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : _count(count) {
	// assert(sizeof(unsigned int) != sizeof(GLuint)); 
	GLCall(glGenBuffers(1, &_rendererId));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {

}

void IndexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererId));
}

void IndexBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}