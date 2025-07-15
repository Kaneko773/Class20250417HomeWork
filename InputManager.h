#pragma once

class InputManager
{
public:
	void FrameStart();//フレームの最初に呼ぶ
	void FrameEnd();//フレームの最後に呼ぶ

	bool GetKeyDown_W();
	bool GetKeyDown_S();
	bool GetKeyDown_M();
	bool GetKeyDown_SPACE();
	bool GetKeyUp_SPACE();

	InputManager(const InputManager&) = delete;
	void operator=(const InputManager&) = delete;

private:
	InputManager();
	virtual ~InputManager() {};

private:
	static InputManager* pInstance;

	int inputW;
	int prevInputW;
	int inputS;
	int prevInputS;
	int inputM;
	int prevInputM;
	int inputSPACE;
	int prevInputSPACE;

public:
	static InputManager* getInstance();
	static void create();
	static void destroy();
};