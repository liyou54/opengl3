#include "../headers/ShaderProgram.h"

ShaderProgram::ShaderProgram(const char * vertexShaderPath,const char * fragmentShaderPath)
{
    vertexFilePath = vertexShaderPath;
    fragmentFilePath = fragmentShaderPath;
    programID =CreatProgram();

}

int ShaderProgram::CreatProgram(){
    vertexShaderID = LoadShader(vertexFilePath,GL_VERTEX_SHADER);
    fragmentShaderID = LoadShader(fragmentFilePath,GL_FRAGMENT_SHADER);
    int PID = glCreateProgram();
    glAttachShader(PID, vertexShaderID);
    glAttachShader(PID, fragmentShaderID);
    glLinkProgram(PID);

    int success ;
    glGetProgramiv(PID,GL_LINK_STATUS,&success);
    if(!success){
        char infoLog[512];
        glGetProgramInfoLog(PID,512,nullptr,infoLog);
        std::cout << "Link Program Error : "<<infoLog<<std::endl;
        return 0;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    return PID;
}

void ShaderProgram::ReloadShader(){
    int reloadProgramID = CreatProgram();
    if(reloadProgramID){
        glDeleteProgram(programID);
        programID = reloadProgramID;
        
    }
}

int ShaderProgram::LoadShader(const char* FilePath,int type){
    std::string strShaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        std::stringstream shaderString;
        shaderFile.open(FilePath);
        shaderString<<shaderFile.rdbuf();

        shaderFile.close();
        strShaderCode = shaderString.str();
    }
    catch(std::exception e){
        std::cout << "Load Shader Error!\n";
        return -1;
    }

    int shaderID = glCreateShader(type);
    const char* cShaderCode = strShaderCode.c_str();
    glShaderSource(shaderID, 1, &cShaderCode, nullptr);
    glCompileShader(shaderID);

    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS,&success);
    if(!success){
        char InfoLog[512];
        glGetShaderInfoLog(shaderID,512,nullptr,InfoLog);
        std::cout <<"compile shader error : "<<InfoLog <<std::endl;
    }
    return shaderID;
}

void ShaderProgram::Start(){
    glUseProgram(programID);
}

void ShaderProgram::Stop(){
    glUseProgram(0);    
}

void ShaderProgram::CleanUp(){
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDetachShader(programID,vertexShaderID);
    glDetachShader(programID,fragmentShaderID);
    glDeleteProgram(programID);
}

void ShaderProgram::SendVarToGLSL(float data,int count,const char * aim,void (func)(int,float))
{
    int varid = glGetUniformLocation(programID,aim);
    func(varid,data);
} 

void ShaderProgram::SendVarToGLSL(float *data,int count,const char * aim,void (func)(int,float*))
{
    int varid = glGetUniformLocation(programID,aim);
    func(varid,data);
}

void ShaderProgram::SendVarToGLSL(float *data,int count,const char * aim,void (func)(int,int,float*))
{
    int varid = glGetUniformLocation(programID,aim);
    func(varid,count,data);
}

void ShaderProgram::SendVarToGLSL(const float *data,int count,const char * aim,void (func)(int,int,unsigned char,const float*)){
    int varid = glGetUniformLocation(programID,aim);
    func(varid,count,GL_FALSE,data);
}

int ShaderProgram::getProgramID(){
    return programID;
}