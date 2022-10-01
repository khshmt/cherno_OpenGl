#pragma once
#include <debugger.hpp>
#include <vertexBuffer.hpp>
#include <vertexBufferLayout.hpp>

class VertexArray {
private:
    unsigned int _rendererId;
public:
    VertexArray();
    ~VertexArray();
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void unBind() const;
};