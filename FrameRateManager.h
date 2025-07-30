#pragma once

class FrameRateManager
{
public:
	void FrameRateUpdate();
	float Get_Deltatime() const;

	FrameRateManager(const FrameRateManager&) = delete;
	void operator=(const FrameRateManager&) = delete;

private:
	FrameRateManager();
	virtual ~FrameRateManager() {};

private:
	static FrameRateManager* pInstance;

	LONGLONG nowTime;
	LONGLONG time;
	float deltaTime;

public:
	static FrameRateManager* getInstance();
	static void create();
	static void destroy();
};
