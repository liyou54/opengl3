#include "../headers/TextureProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
Texture::Texture(const char *TextureFilePath):TextureFilePath(TextureFilePath){
    glGenTextures(1, &TextureID);


}

TextureProgram::TextureProgram(){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::OpenTexture (){
    stbi_set_flip_vertically_on_load(true);
    TextureData = stbi_load(TextureFilePath,&width,&height,&channel,0);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    if(channel == 4)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureData);
    if(channel == 3)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(TextureData);
}

int TextureProgram::addTexture(const char* TextureFilePath){
    Texture* tmp = new Texture(TextureFilePath); 
    Textures.push_back(tmp);
    return tmp->TextureID;
}

void TextureProgram::UseTexture(unsigned int id,int channel,int programid,std::string aim){
    for(auto texture:Textures){
        if (id == texture->TextureID)
        {
            glActiveTexture(GL_TEXTURE0+channel);
            glBindTexture(GL_TEXTURE_2D, texture->TextureID);
            int varid = glGetUniformLocation(programid, aim.c_str());
            glUniform1i(varid, channel);
            texture->OpenTexture();
            break;
        } 
    }
    glBindTexture(GL_TEXTURE_2D,0);

}