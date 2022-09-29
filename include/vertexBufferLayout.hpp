#pragma once 
#include <vector>
#include <assert.h>
#include <GL/glew.h>

struct VertexBufferLayoutElement {
    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch(type) {
            case GL_FLOAT:         return 4;
            case GL_UNSIGNED_INT:  return 4;
            case GL_UNSIGNED_BYTE: return 4;
        }
        assert(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferLayoutElement> _vertexBufferElemnt;
    unsigned int _stride;
public:
    VertexBufferLayout() : _stride(0) {}


    void push(unsigned int count) {
        _vertexBufferElemnt.push_back({ GL_FLOAT, count, false });
        _stride += VertexBufferLayoutElement::getSizeOfType(GL_FLOAT);
    }

    // void push(unsigned int count) {
    //     _vertexBufferElemnt.push_back({ GL_UNSIGNED_INT, 2, false });
    //     _stride += VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_INT);
    // }
    // void push(unsigned int count) {
    //     _vertexBufferElemnt.push_back({ GL_UNSIGNED_BYTE, 2, false });
    //     _stride += VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_BYTE);
    // }
    inline const std::vector<VertexBufferLayoutElement>& getElements() const {return _vertexBufferElemnt;}
    inline unsigned int getStride() const {return _stride;}
};