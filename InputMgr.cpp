#include <iostream>
#include "InputMgr.h"
#include <algorithm>

list<Keyboard::Key> InputMgr::downList;	//
list<Keyboard::Key> InputMgr::ingList;
list<Keyboard::Key> InputMgr::upList;

void InputMgr::ClearInput()
{
	downList.clear();
	upList.clear();
}
void InputMgr::UpdateInput(Event& ev)
{

	switch (ev.type)
	{
	case Event::EventType::KeyPressed:
		//std::cout << "Key Pressed" << ev.key.code << std::endl;
		if (!GetKey(ev.key.code))
		{
			downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);
		}


		break;
	case Event::EventType::KeyReleased:
		//std::cout << "Key Released" << ev.key.code << std::endl;
		ingList.remove(ev.key.code);
		upList.push_back(ev.key.code);

		break;
	}
}

bool InputMgr::GetKeyDown(const Keyboard::Key& key)
{
	return find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKey(const Keyboard::Key& key)
{
	return find(ingList.begin(), ingList.end(), key) != ingList.end();
}

bool InputMgr::GetKeyUp(const Keyboard::Key& key)
{
	return find(upList.begin(), upList.end(), key) != upList.end();
}
