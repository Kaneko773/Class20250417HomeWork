#pragma once

#define KEY_CNT 256

class InputManager
{
public:

	void Update_Key();

	char key_down[KEY_CNT];		//�����ꂽ�u��
	char key_up[KEY_CNT];		//�����ꂽ�u��

	InputManager(const InputManager&) = delete;
	void operator=(const InputManager&) = delete;

private:
	InputManager();
	virtual ~InputManager() {};

private:
	static InputManager* pInstance;

	char keybuf[KEY_CNT];		//�L�[�o�b�t�@ (���t���[��)
	char keybuf_old[KEY_CNT];   //1�O�̃L�[�o�b�t�@(�O�t���[��) 

public:
	static InputManager* getInstance();
	static void create();
	static void destroy();
};