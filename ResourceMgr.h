#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <map>
#include <string>
#include "3rd/SingleTon.h"
#include "3rd/rapidcsv.h"
using namespace std;
using namespace sf;

//�̱���
//(����)���ҽ� �ε� (���Ͽ� �Է�) / ������
// Get()


enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
};

class ResourceMgr : public Singleton<ResourceMgr>
{
public:
	ResourceMgr();
	~ResourceMgr();

	static string FilePath;

	void ReleaseAll();

	bool LoadAll();
	bool Load(ResourceTypes type, string id);

	bool LoadTexture(string id);
	bool LoadFont(string id);
	bool LoadSoundBuffer(string id);

	Texture* GetTexture(string id);
	Font* GetFont(string id);
	SoundBuffer* GetSoundBuffer(string id);



private:
	map<string, Texture*> texMap;
	map<string, Font*> fontMap;
	map<string, SoundBuffer*> soundMap;

};

