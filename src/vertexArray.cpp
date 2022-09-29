#include <vertexArray.hpp>

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &_rendererId));
	GLCall(glBindVertexArray(_rendererId));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &_rendererId));
}

void VertexArray::Bind() const  {
    GLCall(glBindVertexArray(_rendererId));
}
void VertexArray::unBind() const {
    GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    Bind();
    vb.Bind();
    const auto& elements = layout.getElements();
    unsigned int offset{0};
    for(unsigned int i=0; i < elements.size(); ++i) {
        const auto& elem  = elements[i];
        GLCall(glEnableVertexAttribArray(i));
	    //vertex buffer layout specification
	    GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized ? true : false, 2*layout.getStride(), (void*)offset)); 
        offset += elem.count * VertexBufferLayoutElement::getSizeOfType(elem.type) ;
    }
}