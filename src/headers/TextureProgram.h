#pragma once
#include <iostream>
#pragma once

#include <Vector>
# include "glad/glad.h"


class Texture{

public:
    Texture(const char* TextureFilePath);
    void OpenTexture();
    unsigned int TextureID;
    int width,height,channel;
    const char* TextureFilePath;    
    unsigned char* TextureData;

};

class TextureProgram{
private:
    std::vector<Texture*>  Textures;
public:
    int addTexture(const char* TextureFilePath);
    void UseTexture(unsigned int id,int channel,int programid,std::string aim);
    void BindTexture(unsigned int id);
    TextureProgram();
};