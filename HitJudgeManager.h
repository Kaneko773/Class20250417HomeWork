#pragma once

class BoxCollider;
//class Player;
//class Paddle;

class HitJudgeManager
{
public:
	bool HitJudge(BoxCollider* playerCollider, BoxCollider* paddleCollider);
	//bool HitJudge(Player* player, Paddle* paddle);

	HitJudgeManager(const HitJudgeManager&) = delete;
	void operator=(const HitJudgeManager&) = delete;

private:
	HitJudgeManager() {};
	virtual ~HitJudgeManager() {};
private:
	static HitJudgeManager* pInstance;

public:
	static HitJudgeManager* getInstance();
	static void create();
	static void destroy();
};

