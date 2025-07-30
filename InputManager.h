#pragma once

#define KEY_CNT 256

class InputManager
{
public:

	void Update_Key();

	char key_down[KEY_CNT];		//押された瞬間
	char key_up[KEY_CNT];		//離された瞬間

	InputManager(const InputManager&) = delete;
	void operator=(const InputManager&) = delete;

private:
	InputManager();
	virtual ~InputManager() {};

private:
	static InputManager* pInstance;

	char keybuf[KEY_CNT];		//キーバッファ (現フレーム)
	char keybuf_old[KEY_CNT];   //1つ前のキーバッファ(前フレーム) 

public:
	static InputManager* getInstance();
	static void create();
	static void destroy();
};