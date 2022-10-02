#pragma once
#include <string>
#include <debugger.hpp>
#include <vendor/stb_image/stb_image.h>

class Texture{
private:
    unsigned int _rendererId;
    std::string _filePath;
    unsigned char* _localBuffer;
    int _width, _height, _bytesperPixel;
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void unBind() const;

    inline int getWidth() const {return _width;}
    inline int getHeight() const {return _height;}
};