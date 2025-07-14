#include "HitJudgeManager.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Paddle.h"

// 唯一のインスタンス
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
	if (player->_isCollisionResponse) return;//プレイヤーが衝突応答していたら、このフレームではもう判定しない

	if (paddle->Get_m_materialization())
	{
		//実体化してる
		if (HitJudge_materialization(player, paddle))
		{
			paddle->_center += paddle->_movementPerFrame;
			player->_center = { player->_center.Get_x(), paddle->Get_topSide() - player->_size.Get_height() / 2.0f };//パドルの上に立つ

			player->CanJump();
			player->vel = 0;
			player->_isCollisionResponse = true;
			paddle->_isCollisionResponse = true;
		}
	}
	else
	{
		//実体化してない
		float temp = HitJudge_notMaterialization(player, paddle);//パドルの移動ベクトル上で、プレイヤーと当たった場所の割合が返ってくる(-1だと当たってない)
		if (temp != -1)
		{
			paddle->_center += paddle->_movementPerFrame * temp;//当たったとこまで移動
			player->_center = { player->_center.Get_x(), paddle->Get_topSide() - player->_size.Get_height() / 2.0f };//パドルの上に立つ

			paddle->SteppedOn();//パドルを実体化

			player->CanJump();
			player->vel = 0;
			player->_isCollisionResponse = true;
			paddle->_isCollisionResponse = true;
		}
	}
}

float Cross(Vector2<float> vector1, Vector2<float> vector2) {
	return vector1.Get_x() * vector2.Get_y() - vector1.Get_y() * vector2.Get_x();
}
//渡されたベクトル同士が交差してるかどうか
bool IsCross(Vector2<float> startPoint1, Vector2<float> endPoint1, Vector2<float> startPoint2, Vector2<float> endPoint2) {

	Vector2<float> vector1 = endPoint1 - startPoint1;
	Vector2<float> vector2 = endPoint2 - startPoint2;

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
		{ player->Get_leftSide(), player->Get_bottomSide() },
		{ player->Get_leftSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
		{ paddle->Get_leftSide(), paddle->Get_topSide() },
		{ paddle->Get_rightSide(), paddle->Get_topSide() })
		)
		return true;
	//プレイヤーの足元(右下)
	if (IsCross(
		{ player->Get_rightSide(), player->Get_bottomSide() },
		{ player->Get_rightSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
		{ paddle->Get_leftSide(), paddle->Get_topSide() },
		{ paddle->Get_rightSide(), paddle->Get_topSide() })
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
			{ player->Get_leftSide(), player->Get_bottomSide() },
			{ player->Get_leftSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
			{ paddle->Get_leftSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i },
			{ paddle->Get_rightSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i })
			)
			return i;
	}
	//プレイヤーの足元(右下)とパドルの左上
	for (float i = 0; i <= 1.0f; i += 0.5f) {
		if (IsCross(
			{ player->Get_rightSide(), player->Get_bottomSide() },
			{ player->Get_rightSide() + player->_movementPerFrame.Get_x(), player->Get_bottomSide() + player->_movementPerFrame.Get_y() },
			{ paddle->Get_leftSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i },
			{ paddle->Get_rightSide() + paddle->_movementPerFrame.Get_x() * i, paddle->Get_topSide() + paddle->_movementPerFrame.Get_y() * i })
			)
			return i;
	}

	return -1;
}