#pragma once

//#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class YYShader
{
public:
    // 程序ID
    unsigned int ID;

    // 构造器读取并构建着色器
    YYShader(const char* vertexPath, const char* fragmentPath);
    ~YYShader();
    // 使用/激活程序
    void use();
    // uniform工具函数
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVector4(const std::string& name, float v1, float v2, float v3, float v4) const;
};

