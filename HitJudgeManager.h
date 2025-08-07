#pragma once
#include "Vector2.h"

class BoxCollider;
class Player;
class Paddle;

class HitJudgeManager
{
public:
	void ColliderUpdate(Player* player, Paddle* paddle) const;
	float Cross(const Vector2& vector1, const Vector2& vector2) const;
	bool IsCross(Vector2 startPoint1, Vector2 endPoint1, Vector2 startPoint2, Vector2 endPoint2) const;
	bool HitJudge_materialization(BoxCollider* player, BoxCollider* paddle) const;
	float HitJudge_notMaterialization(BoxCollider* player, BoxCollider* paddle) const;

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
