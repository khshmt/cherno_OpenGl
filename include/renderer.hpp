#pragma once
#include <iostream>
#include <GL/glew.h>
#include <assert.h>
#include <vertexArray.hpp>
#include <indexBuffer.hpp>
#include <shader.hpp>

class Renderer {
public:
    void clear() const ;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const ;
};