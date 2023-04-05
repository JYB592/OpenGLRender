#pragma once

//#include <glad/glad.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class YYShader
{
public:
    // ����ID
    unsigned int ID;

    // ��������ȡ��������ɫ��
    YYShader(const char* vertexPath, const char* fragmentPath);
    ~YYShader();
    // ʹ��/�������
    void use();
    // uniform���ߺ���
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVector4(const std::string& name, float v1, float v2, float v3, float v4) const;
};

