#pragma once

#include <vector>

class BoxCollider;
class Player;
class Paddle;

class HitJudgeManager
{
public:
	void ColliderUpdate(Player* player, Paddle* paddle);
	bool HitJudge_materialization(BoxCollider* player, BoxCollider* paddle);
	bool HitJudge_notMaterialization(BoxCollider* player, BoxCollider* paddle);

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
