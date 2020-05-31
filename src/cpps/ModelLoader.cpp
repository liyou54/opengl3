#include "../headers/ModelLoader.h"

// -------------------------------------VBO-------------------------------------
VBO::VBO(int size,int offset ):
 offset(offset), size(size)
{
    glGenBuffers(1, &VBOID); 

}

// -------------------------------------VAO-------------------------------------------
VAO::VAO(int* EBO,int EBOSize,float *data,int datasize,int stride):EBO(EBO),EBOSize(EBOSize),data(data),datasize(datasize),stride(stride)
{
    glGenVertexArrays(1, &VAOID);   
    glGenBuffers(1, &EBOID);
}
// 开启通道
void VAO::OpenChannel(int channel)
{
    glEnableVertexAttribArray(channel);
}
// 关闭通道
void VAO::CloseChannel(int channel){
    glDisableVertexAttribArray(channel);
}
// 添加VBO
unsigned int VAO::AddVBO(int size,int offset)
{
    VBO* tmpVBO = new VBO(size,offset);
    VBOs.push_back(tmpVBO);
    return tmpVBO->VBOID;
}
// 删除VBO
void VAO::DeleteVBO(unsigned int vboid)
{
    UnUseVBO(vboid);
    VBO* vbo = GetVBOById(vboid);
    delete vbo;
    VBOs.erase(std::remove(VBOs.begin(), VBOs.end(), vbo),VBOs.end());
}
// 返回VBO
VBO* VAO::GetVBOById(unsigned int id)
{
    for(auto vbo:VBOs){
        if(vbo->VBOID==id) return vbo;
    }
    return nullptr;
}
// 使用VBO
void VAO::BindVBO(unsigned int id,int channel,int UseType)
{
    VBO* vbo = GetVBOById(id);
    OpenChannel(channel);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER,datasize , data, UseType);
    glVertexAttribPointer(channel, vbo->size, GL_FLOAT, GL_FALSE, stride* sizeof(float), (void*)vbo->offset);
    vboInChannels[channel] = id;
}
// 解绑VBO
void VAO::UnUseVBO(unsigned int channel)
{
    vboInChannels[channel]=0;
    CloseChannel(channel);
}

int VAO::GetChannelbyID(unsigned int id)
{
    for(int i=0;i<16;i++)   
        if (vboInChannels[i]==id)     
            return i;
    return -1;
}

int VAO::GetChannelbyVBO(VBO* vbo)
{
    for(int i=0;i<16;i++)
        if(vbo->VBOID = vboInChannels[i])
            return i;
    return -1;
}

unsigned int VAO::GetVBOIDByChannel(int channel)
{
    return vboInChannels[channel];
}

VBO* VAO::GetVBOByChannel(int channel)
{
    return GetVBOById(vboInChannels[channel]);
}

void VAO::BindVAO()
{
    glBindVertexArray(VAOID);
}

void VAO::UnBindVAO()
{
    glBindVertexArray(0);
}

void VAO::BindEBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOSize, EBO, GL_STATIC_DRAW);
}

