#include "YYModel.h"
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>
#include "YYShader.h"
#include <glm-0.9.9.8/glm/glm.hpp>
#include <glm-0.9.9.8/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.9.8/glm/gtc/type_ptr.hpp>
#include "YYCamera.h"
#include <memory>

using namespace std;

extern YYCamera camera;
extern  int SCR_WIDTH;
extern  int SCR_HEIGHT;

YYShader* YYModel::defShader = nullptr;

YYModel::YYModel(float* pVertices, int pVSize)
{
	vertices = pVertices;
    vSize = pVSize;

    glGenVertexArrays(1, &VAO);

    //�������㻺�����
    glGenBuffers(1, &VBO);
    
    //////////////////////////////////////////////////��������
    texture1Num = 2;
    texture1[0] = setTexture("Texture/container.jpg", GL_RGB);
    texture1[1] = setTexture("Texture/awesomeface.png", GL_RGBA);

    translateModelM = glm::mat4(1.0f);
    rotateModelM = glm::mat4(1.0f);
    scaleModelM = glm::mat4(1.0f);
}
YYModel::~YYModel()
{
    if (ourShader)
    {
        delete ourShader;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}

void YYModel::Draw()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //���������ݼ��ص����㻺�������
    glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);

    //////////////////////////////////////////////////���ö�������ָ��
    // λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // ��������
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //////////////////////////////////////////////////����shader
    YYShader* shader = ourShader ? ourShader : YYModel::defShader;
    shader->use();
    //����ȫ�ֱ�����ʹ��shader
    shader->setInt("texture1", 0);
    shader->setInt("texture2", 1);

    //////////////////////////////////////////////////����������
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1[1]);

    //Mģ�ͱ任
    glm::mat4 modelM = translateModelM * rotateModelM;
    modelM = modelM * scaleModelM;
    unsigned int modelid = glGetUniformLocation(shader->ID, "modelM");
    glUniformMatrix4fv(modelid, 1, GL_FALSE, glm::value_ptr(modelM));
    //V�ӿڱ任
    glm::mat4 viewM = camera.GetViewMatrix();
    unsigned int viewid = glGetUniformLocation(shader->ID, "viewM");
    glUniformMatrix4fv(viewid, 1, GL_FALSE, glm::value_ptr(viewM));
    //PͶӰ�任
    glm::mat4 projectionM = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    unsigned int projectionid = glGetUniformLocation(shader->ID, "projectionM");
    glUniformMatrix4fv(projectionid, 1, GL_FALSE, glm::value_ptr(projectionM));

    //���㻺�����
    //cout << vertices[1] << endl;
    glDrawArrays(GL_TRIANGLES, 0, vSize / sizeof(float) / 5);
    //Ԫ�ػ������
    //glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

    //���߿�ģʽ����������
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void YYModel::SetEspecialShader(const char* vstr, const char* fstr)
{
    ourShader = new YYShader(vstr, fstr);
}

void YYModel::Translate(float x, float y, float z)
{
    translateModelM = glm::translate(translateModelM, glm::vec3(x, y, z));
}

void YYModel::Rotate(float angle, float x, float y, float z)
{
    rotateModelM = glm::rotate(rotateModelM, glm::radians(angle), glm::vec3(x, y, z));
}

void YYModel::Scale(float s)
{
    scaleModelM = glm::scale(scaleModelM, glm::vec3(s, s, s));
}

unsigned int YYModel::setTexture(const char* path, int kind)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // ���ز���������
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        stbi_set_flip_vertically_on_load(true);
        glTexImage2D(GL_TEXTURE_2D, 0, kind, width, height, 0, kind, GL_UNSIGNED_BYTE, data);
        //�������е�mipmap
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}
