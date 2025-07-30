#include "HitJudgeManager.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Paddle.h"

HitJudgeManager* HitJudgeManager::pInstance = nullptr;
HitJudgeManager* HitJudgeManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new HitJudgeManager();
	}
	return pInstance;
}

void HitJudgeManager::create()
{
	if (pInstance == nullptr)
	{
		pInstance = new HitJudgeManager();
	}
}

void HitJudgeManager::destroy()
{
	if (pInstance != nullptr)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void HitJudgeManager::ColliderUpdate(Player* player, Paddle* paddle)
{
	if (player->isCollisionResponse) return;//プレイヤーが衝突応答していたら、このフレームではもう判定しない

	//実体化してる
	if (paddle->Get_m_materialization())
	{
		paddle->MoveByRate();//パドルは先に動かす
		if (HitJudge_materialization(player, paddle))
		{
			player->FixedMove({ player->center.x, paddle->fourSides.topSide - player->size.height / 2.0f });//パドルの上に立つ

			player->CanJump();
			player->vel_y = 0;
			player->isCollisionResponse = true;
			paddle->isCollisionResponse = true;
		}
	}
	//実体化してない
	else
	{
		float temp = HitJudge_notMaterialization(player, paddle);//パドルの移動ベクトル上で、プレイヤーと当たった場所の割合が返ってくる(-1だと当たってない)
		if (temp != -1)
		{
			paddle->MoveByRate(temp);//当たったとこまで移動
			player->FixedMove({ player->center.x, paddle->fourSides.topSide - player->size.height / 2.0f });//パドルの上に立つ

			paddle->SteppedOn();//パドルを実体化

			player->CanJump();
			player->vel_y = 0;
			player->isCollisionResponse = true;
			paddle->isCollisionResponse = true;
		}
	}
}

float HitJudgeManager::Cross(const Vector2& vector1, const Vector2& vector2) const
{
	return vector1.x * vector2.y - vector1.y * vector2.x;
}
//渡されたベクトル同士が交差してるかどうか
bool HitJudgeManager::IsCross(Vector2 startPoint1, Vector2 endPoint1, Vector2 startPoint2, Vector2 endPoint2) const
{
	Vector2 vector1 = endPoint1 - startPoint1;
	Vector2 vector2 = endPoint2 - startPoint2;

	if (Cross(vector1, startPoint2 - startPoint1) * Cross(vector1, endPoint2 - startPoint1) < 0 &&
		Cross(vector2, startPoint1 - startPoint2) * Cross(vector2, endPoint1 - startPoint2) < 0)
		return true;

	return false;
}
//実体化してるパドルとの判定
bool HitJudgeManager::HitJudge_materialization(BoxCollider* player, BoxCollider* paddle)
{
	//プレイヤーの足元(左下)
	if (IsCross(
		{ player->fourSides.leftSide, player->fourSides.bottomSide },
		{ player->fourSides.leftSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
		{ paddle->fourSides.leftSide, paddle->fourSides.topSide },
		{ paddle->fourSides.rightSide, paddle->fourSides.topSide })
		)
		return true;
	//プレイヤーの足元(右下)
	if (IsCross(
		{ player->fourSides.rightSide, player->fourSides.bottomSide },
		{ player->fourSides.rightSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
		{ paddle->fourSides.leftSide, paddle->fourSides.topSide },
		{ paddle->fourSides.rightSide, paddle->fourSides.topSide })
		)
		return true;

	return false;
}
//実体化してないパドルとの判定
float HitJudgeManager::HitJudge_notMaterialization(BoxCollider* player, BoxCollider* paddle)
{
	//プレイヤーの左右足元（２点）からの移動ベクトルとパドルの上辺　（最大6回判定）

	//プレイヤーの足元(左下)とパドルの上辺
	for (float i = 0; i <= 1.0f; i += 0.5f) {
		if (IsCross(
			{ player->fourSides.leftSide, player->fourSides.bottomSide },
			{ player->fourSides.leftSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
			{ paddle->fourSides.leftSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i },
			{ paddle->fourSides.rightSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i })
			)
			return i;
	}
	//プレイヤーの足元(右下)とパドルの左上
	for (float i = 0; i <= 1.0f; i += 0.5f) {
		if (IsCross(
			{ player->fourSides.rightSide, player->fourSides.bottomSide },
			{ player->fourSides.rightSide + player->movementPerFrame.x, player->fourSides.bottomSide + player->movementPerFrame.y },
			{ paddle->fourSides.leftSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i },
			{ paddle->fourSides.rightSide + paddle->movementPerFrame.x * i, paddle->fourSides.topSide + paddle->movementPerFrame.y * i })
			)
			return i;
	}

	return -1;
}