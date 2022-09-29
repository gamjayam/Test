#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace std;
using namespace sf;

//����ƽ �Լ��� �̿��ؼ� Ű���� �� ���콺 �Է��� �˻��� �� �ִ� Ŭ����

class InputMgr
{
public:
	static void ClearInput();
	static void UpdateInput(Event& ev);


	static bool GetKeyDown(const Keyboard::Key& key);
	static bool GetKey(const Keyboard::Key& key);
	static bool GetKeyUp(const Keyboard::Key& key);


private:
	static list<Keyboard::Key> downList;	//
	static list<Keyboard::Key> ingList;		//
	static list<Keyboard::Key> upList;		//


};

