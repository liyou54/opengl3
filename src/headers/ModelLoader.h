#pragma once
#include "glad/glad.h"
#include <Vector>
#include <algorithm>
// VBO 类
class VBO
{   

public:
    unsigned int VBOID;
    int offset;
    int size;
    VBO( int offset, int size);

};

class VAO
{
private:
    unsigned int VAOID;
    unsigned int EBOID;
    std::vector<VBO*> VBOs;
    int *EBO;
    // 全部VBO步长
    int stride;
    // VBO数据
    float* data;
    // 全部data大小，以字节单位
    int datasize;
    int EBOSize;
    unsigned int vboInChannels[16];
public:
    VAO(int* EBO,int EBOSize,float *data,int datasize,int stride);
    VBO* GetVBOById(unsigned int id);
    void SetVBOByID(unsigned int id,int channel);
    void CloseChannel(int channel);
    void OpenChannel(int channel);
    unsigned int  AddVBO(int size,int offset); 
    void DeleteVBO(unsigned int VBOID);
    void BindVAO();
    void BindEBO();
    void UnBindVAO();
    void BindVBO(unsigned int id,int channel,int UseType);
    void UnUseVBO(unsigned int id);
    int GetChannelbyID(unsigned int id);
    int GetChannelbyVBO(VBO* vbo);
    unsigned int GetVBOIDByChannel(int channel);
    VBO* GetVBOByChannel(int channel);
    
};
