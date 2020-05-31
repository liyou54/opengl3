#pragma once    

#include "Window.h"
#include "ModelLoader.h"
#include "ShaderProgram.h"
#include "EnumStatus.h"
#include "TextureProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include<string>


float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上前 0
     0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下前 1
    -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下前 2 
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上前 3
     0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上后 4 
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下后 5
    -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下后 6
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上后 7
};

int indices[] = { // 注意索引从0开始! 
    6,5,4, 4,7,6,
    2,1,0, 0,3,2,
    3,7,6, 6,2,3,
    0,4,5, 5,1,0,
    6,5,1, 1,2,6,
    7,4,0, 0,3,7
        };

const char* VertexShaderFilePath = "D:\\job\\opengl3\\opengl3\\src\\shaderFile\\vertexShader.vs";
const char*FragmentShaderFilePath = "D:\\job\\opengl3\\opengl3\\src\\shaderFile\\fragmentShader.fs";
const char* TextureFilePath1 = "D:\\job\\opengl3\\opengl3\\texture\\wall.jpg";
const char* TextureFilePath2 = "D:\\job\\opengl3\\opengl3\\texture\\awesomeface.png";

int main()
{
    EnumStatus mDisplayState;
    Window mWindow(false,4,0,800,600,"MyWindow");
    mWindow.InitWindow();


    ShaderProgram mShader(VertexShaderFilePath,FragmentShaderFilePath);
    TextureProgram mTexture;

    
    VAO mVAO(indices,sizeof(indices),vertices,sizeof(vertices),8);
    unsigned int tex1 = mTexture.addTexture(TextureFilePath1);
    unsigned int tex2 = mTexture.addTexture(TextureFilePath2);
    int mShaderid = mShader.getProgramID();
    unsigned int pos = mVAO.AddVBO(3,0);
    unsigned int col = mVAO.AddVBO(3,3*4);
    unsigned int tex = mVAO.AddVBO(2,6*4);
    mVAO.BindVAO();
    mVAO.BindEBO();
    glEnableClientState(GL_VERTEX_ARRAY);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    mVAO.BindVBO(pos ,0 , GL_STATIC_DRAW);
    mVAO.BindVBO(col,1,GL_STATIC_DRAW);
    mVAO.BindVBO(tex,2,GL_STATIC_DRAW);
    mShader.Start();
    mTexture.UseTexture(tex1,0,mShaderid,std::string("Texture1"));
    mTexture.UseTexture(tex2,1,mShaderid,std::string("Texture2"));

    glm::mat4 trans;
    
    glm::mat4 model;
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    glm::mat4 view;
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800 / 600.f, 0.1f, 100.0f);


    glEnable(GL_DEPTH_TEST);

    while(!mWindow.IsRequestCloseWindow())
    {
        
        // trans = glm::translate(trans, glm::vec3(0.001, .001f, 0.0f));
        trans = glm::rotate(trans, glm::radians(.1f),glm::vec3(0.5,0.5,0.));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mShader.Start();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex2); 
        mShader.SendVarToGLSL(glfwGetTime(),              1,  "time", glUniform1f);
        mShader.SendVarToGLSL(glm::value_ptr(trans),      1, "trans", glUniformMatrix4fv);
        mShader.SendVarToGLSL(glm::value_ptr(model),      1, "model", glUniformMatrix4fv);
        mShader.SendVarToGLSL(glm::value_ptr(view),       1, "view", glUniformMatrix4fv);
        mShader.SendVarToGLSL(glm::value_ptr(projection), 1, "projection", glUniformMatrix4fv);
        mVAO.BindVAO();

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        mShader.Stop();
        mDisplayState = mWindow.UpdateWindow();
        if(mDisplayState == EnumStatus::RELOADSTATUS){
            mShader.ReloadShader();
            mShader.Start();
        mTexture.UseTexture(tex1,0,mShaderid,std::string("Texture1"));
        mTexture.UseTexture(tex2,1,mShaderid,std::string("Texture2"));
        }
    }

    mWindow.DestroyWindow();
    return 0;
}