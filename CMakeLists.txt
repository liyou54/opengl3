cmake_minimum_required(VERSION 3.2)

if( MINGW )
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -O0 -g -Wall -Wunused-function -pthread")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -pthread")
        message("MINGW - Debug mode")
    elseif( CMAKE_BUILD_TYPE STREQUAL "Release" ) # debug
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -O2 -pthread -Wunused-function")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -pthread")
        message("MINGW - Release mode")
    endif() # Debug
    # 
    if( PROJECT_ARCHITECTURE STREQUAL "x64" ) # x64
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    elseif(PROJECT_ARCHITECTURE STREQUAL "x86") # x86
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    endif() # x64
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} " )
    set( CMAKE_EXECUTABLE_SUFFIX ".exe" )
endif() # MINGW
   
if( APPLE )
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g -Wall -Wunused-function -pthread")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -pthread")
        message("CLANG - Debug mode")
    elseif( CMAKE_BUILD_TYPE STREQUAL "Release" ) # debug
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread -Wunused-function")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -pthread")
        message("CLANG - Release mode")
    endif() # Debug
    #
    if( PROJECT_ARCHITECTURE STREQUAL "x64" ) # x64
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    elseif(PROJECT_ARCHITECTURE STREQUAL "x86") # x86
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    endif() # x64
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} " )
endif() # CLANG
 
# Microsoft Visual C++ Compilers
if(MSVC)
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast /Gy /Oi /Oy /O2 /Ot /Zi /EHsc ")
    endif()
    if(CMAKE_CL_64)
        set( PROJECT_ARCHITECTURE "x64" )
    else(CMAKE_CL_64)
        set( PROJECT_ARCHITECTURE "x86" )
    endif(CMAKE_CL_64) 
    #
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    #
    set( CMAKE_EXECUTABLE_SUFFIX ".exe" )
endif()


#指定项目名称
PROJECT(main)

#将main.cpp 赋值给SOURCE 变量
SET(SOURCE ${PROJECT_SOURCE_DIR}/src/main.cpp) 
  
#指定头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/headers)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
#指定链接库文件目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
file(GLOB USER_LIBS_PATH ./src/cpps/*.cpp)
#将main.cpp生成可执行文件main 
ADD_EXECUTABLE(main ${SOURCE} ${USER_LIBS_PATH})
 
#指定main 链接库
TARGET_LINK_LIBRARIES(main libglfw3dll.a libglad.a  )
 
