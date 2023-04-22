#pragma once

#include <glm-0.9.9.8/glm/glm.hpp>
#include "YYMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class YYShader;

class YYModel
{
public:
	static YYShader* defShader;

	// model data 
	vector<Texture> textures_loaded;	// �洢��ĿǰΪֹ���ص����������Ż���ȷ����������س���һ�Ρ�
	vector<YYMesh>    meshes; 
	string directory; //modle�ļ�����·��
	bool gammaCorrection;


	YYModel(string const& path, bool gamma = false);
	virtual ~YYModel();
	void Draw();

	void SetEspecialShader(const char* vstr, const char* fstr);

	void Translate(float x, float y, float z);
	void Rotate(float angle, float x, float y, float z);
	void Scale(float s);

protected:
	YYShader* ourShader;

	glm::mat4 translateModelM;
	glm::mat4 rotateModelM;
	glm::mat4 scaleModelM;

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const& path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);

    YYMesh processMesh(aiMesh* mesh, const aiScene* scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);