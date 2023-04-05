#include "YYModelManager.h"
#include "YYModel.h"
#include "YYShader.h"

YYModelManager* YYModelManager::modelManager = new YYModelManager();

YYModelManager::~YYModelManager()
{
	for (int i = 0; i < Models.size(); ++i)
	{
		delete Models[i];
	}

	Models.clear();
}

void YYModelManager::init()
{
	YYModel::defShader = new YYShader("ShaderCode/shader.vs", "ShaderCode/shader.fs");
}

YYModel* YYModelManager::addModel(float* pVertices, int pVSize)
{
	YYModel* mm = new YYModel(pVertices, pVSize);
	Models.push_back(mm);
	return mm;
}

void YYModelManager::Draw()
{
	for (int i = 0; i < Models.size(); ++i)
	{
		Models[i]->Draw();
	}
}
