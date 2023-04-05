#version 330 core
layout (location = 0) in vec3 aPos;//位置0的顶点位置属性
layout (location = 1) in vec2 aTexCoord;//位置1的顶点纹理属性

out vec2 TexCoord;//输出纹理坐标

uniform mat4 modelM; //M模型变换
uniform mat4 viewM; //V视口变换
uniform mat4 projectionM; //P投影变换
void main()
{
   TexCoord = aTexCoord;

   gl_Position = projectionM * viewM  * modelM * vec4(aPos, 1.0);
}