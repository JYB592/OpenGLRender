#pragma once
#include<vector>
#include<string>

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
	YYModel* addModel(string const& path, bool gamma = false);
	void Draw();

protected:
	vector<YYModel*> Models;
};
