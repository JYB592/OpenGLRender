#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <glm-0.9.9.8/glm/glm.hpp>
#include <glm-0.9.9.8/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.9.8/glm/gtc/type_ptr.hpp>

#include "YYShader.h"
#include "YYCamera.h"
#include "YYWindow.h"
#include "YYModelManager.h"
#include "YYModel.h"

using namespace std;

// settings
 int SCR_WIDTH = 800;
 int SCR_HEIGHT = 600;

// camera
YYCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// YYWindow
GLFWwindow* Window;

// update
float deltaTime = 0; // 当前帧与上一帧的时间差
float fpsDeltaTime = 1.0f / 90.0f;
float fpsDeltaTimeLast= 0;

int main(void)
{
    GLFWwindow* YYWindow = YYWindow::createWindow();

    //////////////////////////////////////////////////顶点数据
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    //////////////////////////////////////////////////元素索引绘制
    //unsigned int indices[] = { //顶点索引
    //    // 注意索引从0开始! 
    //    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    //    // 这样可以由下标代表顶点组合成矩形

    //    0, 1, 3, // 第一个三角形
    //    1, 2, 3  // 第二个三角形
    //};
    //创建元素缓冲对象
    //unsigned int EBO;
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    ////将元素数据加载到元素缓冲对象中
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //开启深度测试
    glEnable(GL_DEPTH_TEST);

    //添加灯模型
    //YYModelManager::GetInstance()->init();
    //YYModel* m1 = YYModelManager::GetInstance()->addModel("");
    //m1->Translate(0, 2, -5);
    //m1->Scale(0.5);
    //m1->SetEspecialShader("ShaderCode/shader.vs", "ShaderCode/lightShader.fs");
    ////添加其他模型
    //YYModel* m2 = YYModelManager::GetInstance()->addModel("");
    //m2->Translate(0, -2, -5);
    //m2->Rotate(30, 1, 0, 0);
    //m2->Scale(1.5);

    //////////////////////////////////////////////////渲染循环
    while (!glfwWindowShouldClose(YYWindow))
    {
        float currentFrame = (float)glfwGetTime();
        float dtime = currentFrame - fpsDeltaTimeLast;
        if (dtime < fpsDeltaTime) { continue; }
        deltaTime = currentFrame - fpsDeltaTimeLast;
        fpsDeltaTimeLast = currentFrame;

        cout << "FPS: " << ceil(1.0f / deltaTime) << endl;

        //输入事件
        YYWindow::processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        //清除颜色，深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        YYModelManager::GetInstance()->Draw();
     
        //交换颜色缓冲，将窗口像素值画到屏幕上
        glfwSwapBuffers(YYWindow);
    }

    //释放资源
    glfwTerminate();

    return 0;
}