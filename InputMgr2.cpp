#include <iostream>
#include "InputMgr2.h"
#include <algorithm>

vector<bool> InputMgr2::downList(Keyboard::Key::KeyCount);	//
vector<bool> InputMgr2::ingList(Keyboard::Key::KeyCount);
vector<bool> InputMgr2::upList(Keyboard::Key::KeyCount);

void InputMgr2::ClearInput()
{
	fill(downList.begin(), downList.end(), false);
	fill(upList.begin(), upList.end(), false);
}
void InputMgr2::UpdateInput(Event& ev)
{

	switch (ev.type)
	{
	case Event::EventType::KeyPressed:
		//std::cout << "Key Pressed" << ev.key.code << std::endl;
		if (ev.key.code != Keyboard::Key::Unknown && !ingList[(int)ev.key.code])
		{
			downList[(int)ev.key.code] = true;
			ingList[(int)ev.key.code] = true;
		}
		break;
	case Event::EventType::KeyReleased:
		//std::cout << "Key Released" << ev.key.code << std::endl;
		if (ev.key.code != Keyboard::Key::Unknown)
		{
			ingList[(int)ev.key.code] = false;
			upList[(int)ev.key.code] = true;
		}


		break;
	}
}

bool InputMgr2::GetKeyDown(const Keyboard::Key& key)
{
	return downList[(int)key];
}

bool InputMgr2::GetKey(const Keyboard::Key& key)
{
	return ingList[(int)key];
}

bool InputMgr2::GetKeyUp(const Keyboard::Key& key)
{
	return upList[(int)key];
}
