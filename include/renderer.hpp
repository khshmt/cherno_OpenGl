#pragma once
#include <iostream>
#include <GL/glew.h>
#include <assert.h>

#define GLCall(x) GlClearError();\
x;\
assert(GlLogCall(#x, __FILE__, __LINE__))

void GlClearError();
bool GlLogCall(const char* function, const char* file, int line);

