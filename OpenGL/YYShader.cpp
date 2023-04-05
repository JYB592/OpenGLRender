#include "YYShader.h"
#include <glad/glad.h> 

YYShader::YYShader(const char* vertexPath, const char* fragmentPath)
{
    // 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ��֤ifstream��������׳��쳣��
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // ���ļ�
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // ��ȡ�ļ��Ļ������ݵ���������
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // �ر��ļ�������
        vShaderFile.close();
        fShaderFile.close();
        // ת����������string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    //����������ɫ������
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //�Ѷ�����ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    //��ⶥ����ɫ���Ƿ����
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //����ƬԪ��ɫ������
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //��ƬԪ��ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    //���ƬԪ��ɫ���Ƿ����
    int  fSuccess;
    char fInfoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fSuccess);
    if (!fSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, fInfoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fInfoLog << std::endl;
    }

    //////////////////////////////////////////////////������ɫ������
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    //��������Ƿ����
    int linkSuccess;
    char linkInfoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        glGetProgramInfoLog(ID, 512, NULL, linkInfoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << linkInfoLog << std::endl;
    }
    //ɾ����ɫ�����󣬲���Ҫ��
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
YYShader::~YYShader()
{
    glDeleteProgram(ID);
}
void YYShader::use()
{
    glUseProgram(ID);
}

void YYShader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void YYShader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void YYShader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void YYShader::setVector4(const std::string& name, float v1, float v2, float v3, float v4) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4);
}
