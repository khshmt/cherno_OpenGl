#include <renderer.hpp>


void GlClearError() {
	while(glGetError() != GL_NO_ERROR); //GL_NO_ERROR = 0
}

bool GlLogCall(const char* function, const char* file, int line) {
	auto error = glGetError();
	while(error) {
		std::cout << "[OpenGl Error] (" << error << ")"<< ": " << function << ": "
		<< file<< ": " << line << ": " << std::endl;
		return false;
	}
	return true;
}