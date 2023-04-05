#version 330 core
out vec4 FragColor;//输出的颜色值
in vec2 TexCoord;//传入的纹理坐标

uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}