#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace std;
using namespace sf;

class InputMgr2
{
public:
	static void ClearInput();
	static void UpdateInput(Event& ev);


	static bool GetKeyDown(const Keyboard::Key& key);
	static bool GetKey(const Keyboard::Key& key);
	static bool GetKeyUp(const Keyboard::Key& key);


private:
	static vector<bool> downList;	//
	static vector<bool> ingList;		//
	static vector<bool> upList;		//


};

