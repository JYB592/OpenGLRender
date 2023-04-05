#pragma once

#include <glm-0.9.9.8/glm/glm.hpp>

class YYShader;

class YYModel
{
public:
	static YYShader* defShader;

	YYModel(float* pVertices, int size);
	virtual ~YYModel();
	void Draw();

	void SetEspecialShader(const char* vstr, const char* fstr);

	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float s);

protected:
	float* vertices;
	int vSize;
	unsigned int VAO;
	unsigned int VBO;
	YYShader* ourShader;
	unsigned int texture1[6];
	unsigned int texture1Num;

	glm::mat4 translateModelM;
	glm::mat4 rotateModelM;
	glm::mat4 scaleModelM;

	unsigned int setTexture(const char* path, int kind);
};