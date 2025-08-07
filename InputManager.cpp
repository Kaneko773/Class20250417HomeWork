#include "InputManager.h"
#include "DxLib.h"

InputManager::InputManager() {
	for (int i = 0; i < KEY_CNT; ++i)
	{
		keybuf[i] = 0;
		keybuf_old[i] = 0;
		key_down[i] = 0;
		key_up[i] = 0;
	}

}

// 唯一のインスタンス
InputManager* InputManager::pInstance = nullptr;
InputManager* InputManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new InputManager();
	}
	return pInstance;
}

void InputManager::create()
{
	if (pInstance == nullptr)
	{
		pInstance = new InputManager();
	}
}

void InputManager::destroy()
{
	if (pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}


void InputManager::Update_Key()
{
	for (int i = 0; i < KEY_CNT; ++i)
	{
		keybuf_old[i] = keybuf[i];
	}

	GetHitKeyStateAll(keybuf);

	for (int i = 0; i < KEY_CNT; ++i)
	{
		int key_xor = keybuf[i] ^ keybuf_old[i];
		key_down[i] = key_xor & keybuf[i];
		key_up[i] = key_xor & keybuf_old[i];
	}
}
