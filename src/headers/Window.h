#pragma once
#include "EnumStatus.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Window
{
public:
    Window(bool withprofilecore,int major,int minor,int width,int height,const char*title);
    // 初始化窗口
    void InitWindow();
    // 更新窗口
    EnumStatus UpdateWindow();
    // 删除窗口
    void DestroyWindow();
    //窗口是否需要关闭
    bool  IsRequestCloseWindow();

private:
    // 窗口大小
    int _width, _height;
    // 标题
    const char* _title;
    // 是否开启核心模式
    bool _withprofilecore;
    // 版本号
    int _major,_minor;
    // GlfwWinodw
    struct GLFWwindow* _mwindow;
    // 窗口大小变更回调
    static void _FrameBufferSizeChangedCallback(GLFWwindow *window,int width,int height);
    // 事件监听
    EnumStatus _ProcessEvents();
};