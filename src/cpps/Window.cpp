#include "../headers/Window.h"


//  init
Window::Window(bool withprofilecore,int major,int minor,
                int width,int height,const char*title):
_withprofilecore(withprofilecore),_major(major),_minor(minor),
_width(width),_height(height),_title(title)
{

}

// 窗口大小改变回调
void Window::_FrameBufferSizeChangedCallback (GLFWwindow *window, int width, int height)
{
    glViewport (0, 0, width,height);
}

// 删除窗口
void Window::DestroyWindow()
{
    glfwDestroyWindow(_mwindow);
    glfwTerminate();
    _mwindow = nullptr;
}

// 按键值
EnumStatus Window::_ProcessEvents()
{
    if(glfwGetKey(_mwindow,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(_mwindow, true);
        return EnumStatus::ESCSTATUS;
    }
    else if(glfwGetKey(_mwindow,GLFW_KEY_R)==GLFW_PRESS){
        return EnumStatus::RELOADSTATUS;
    }
}

// 设置窗口关闭状态
bool Window::IsRequestCloseWindow()
{
    return glfwWindowShouldClose(_mwindow);
}

// 更新窗口
EnumStatus Window::UpdateWindow()
{
    // 监视按键
    glfwPollEvents();
    // 交换缓存
    glfwSwapBuffers(_mwindow);
    // 返回按键
    return _ProcessEvents();
}

// 窗口初始化
void Window::InitWindow()
{
    // glfw初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,_minor);
    if(_withprofilecore) glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    _mwindow = glfwCreateWindow(_width,_height,_title,nullptr,nullptr);
    if(!_mwindow) 
    {
        std::cout<<"ERROR : Failed Creat Window!"<<std::endl;
        return;
    }

    // 设置上下文
    glfwMakeContextCurrent(_mwindow);

    //加载Glad
    if(!gladLoadGL())
    {
        std::cout<<"ERROR :Fail to Load Glad!"<<std::endl;
        DestroyWindow();
        return;
    } 

    //设置窗口大小改变的回调函数
    glfwSetFramebufferSizeCallback(_mwindow,_FrameBufferSizeChangedCallback);

}