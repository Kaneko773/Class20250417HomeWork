#include "InputManager.h"
#include "DxLib.h"

InputManager::InputManager() {
	inputW = prevInputW = 0;
	inputS = prevInputS = 0;
	inputM = prevInputM = 0;
	inputSPACE = prevInputSPACE = 0;
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

void InputManager::FrameStart()
{
	inputW = CheckHitKey(KEY_INPUT_W);
	inputS = CheckHitKey(KEY_INPUT_S);
	inputM = CheckHitKey(KEY_INPUT_M);
	inputSPACE = CheckHitKey(KEY_INPUT_SPACE);
}

void InputManager::FrameEnd()
{
	prevInputW = inputW;
	prevInputS = inputS;
	prevInputM = inputM;
	prevInputSPACE = inputSPACE;
}

bool InputManager::GetKeyDown_W()
{
	return inputW && prevInputW == 0;
}

bool InputManager::GetKeyDown_S()
{
	return inputS == 1 && prevInputS == 0;
}

bool InputManager::GetKeyDown_M()
{
	return inputM == 1 && prevInputM == 0;
}

bool InputManager::GetKeyDown_SPACE()
{
	return inputSPACE == 1 && prevInputSPACE == 0;
}

bool InputManager::GetKeyUp_SPACE()
{
	return inputSPACE == 0 && prevInputSPACE == 1;
}
