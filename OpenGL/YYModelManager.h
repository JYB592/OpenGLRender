#pragma once
#include<vector>

using namespace std;

class YYModel;

class YYModelManager
{
public:
	static YYModelManager* GetInstance()
	{
		return modelManager;
	}

	virtual ~YYModelManager();

private:
	static YYModelManager* modelManager;

public:
	void init();
	YYModel* addModel(float* pVertices, int pVSize);
	void Draw();

protected:
	vector<YYModel*> Models;
};
