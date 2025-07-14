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
	if (paddle->Get_m_materialization())
	{
#if 0
		IsCrossing(
			_lineSegment1.startPoint.position, _lineSegment1.endPoint.position,
			_lineSegment2.startPoint.position, _lineSegment2.endPoint.position
		)
#endif
		//実体化してる
		if (HitJudge_materialization(player, paddle))
		{
			paddle->_center += paddle->_movementPerFrame;
			if (player->_movementPerFrame.Get_x() != 0) {

			}
			else {
				player->_center = { player->_center.Get_x(), paddle->Get_topSide() - player->_size.Get_height() / 2.0f };
			}

			player->CanJump();
			player->vel = 0;
			player->_isCollisionResponse = true;
			paddle->_isCollisionResponse = true;

			//実体化したパドルは衝突応答時にそのまま下がって、その上にプレイヤーが立つ

			//パドルの上に立つ(衝突応答)

			//まだ立てない//////////////////////////////////////////////////////////////////////////////////
		}
	}
	else
	{
		//実体化してない
		if (HitJudge_notMaterialization(player, paddle))
		{
			//実体化してないパドルとプレイヤーは当たったとこに移動→上にプレイヤーを立たせる

			//プレイヤーとパドルを当たった位置に移動（衝突応答）
			//パドルは実体化、当たった位置に移動
			//プレイヤーはパドルの上に立たせる、立ってる判定にする
		}	
	}
}

float Cross(Vector2<float> vector1, Vector2<float> vector2) {
	return vector1.Get_x() * vector2.Get_y() - vector1.Get_y() * vector2.Get_x();
}
//実体化してるパドルとの判定
bool HitJudgeManager::HitJudge_materialization(BoxCollider* player, BoxCollider* paddle)
{
	//プレイヤーの足元(左下)
	Vector2<float> startPoint1 = { player->Get_leftSide(), player->Get_bottomSide() };//左下
	Vector2<float> endPoint1 = {startPoint1.Get_x() + player->_movementPerFrame.Get_x(), startPoint1.Get_y() + player->_movementPerFrame.Get_y() };
	Vector2<float> startPoint2 = { paddle->Get_leftSide(), paddle->Get_topSide() };//パドルの上辺
	Vector2<float> endPoint2 = { paddle->Get_rightSide(), paddle->Get_topSide() };

	// ベクトルP1Q1
	Vector2<float> vector1 = endPoint1 - startPoint1;
	// ベクトルP2Q2
	Vector2<float> vector2 = endPoint2 - startPoint2;
	//
	// 以下条件をすべて満たすときが交差となる
	//
	//    P1Q1 x P1P2 と P1Q1 x P1Q2 が異符号
	//                かつ
	//    P2Q2 x P2P1 と P2Q2 x P2Q1 が異符号
	//
	if (Cross(vector1, startPoint2 - startPoint1) * Cross(vector1, endPoint2 - startPoint1) < 0 &&
		Cross(vector2, startPoint1 - startPoint2) * Cross(vector2, endPoint1 - startPoint2) < 0)
		return true;

	//プレイヤーの足元(右下)
	Vector2<float> startPoint3 = { player->Get_rightSide(), player->Get_bottomSide() };//左下
	Vector2<float> endPoint3 = { startPoint3.Get_x() + player->_movementPerFrame.Get_x(), startPoint3.Get_y() + player->_movementPerFrame.Get_y() };
	Vector2<float> startPoint4 = { paddle->Get_leftSide(), paddle->Get_topSide() };//パドルの上辺
	Vector2<float> endPoint4 = { paddle->Get_rightSide(), paddle->Get_topSide() };

	// ベクトルP1Q1
	Vector2<float> vector3 = endPoint3 - startPoint3;
	// ベクトルP2Q2
	Vector2<float> vector4 = endPoint4 - startPoint4;
	//
	// 以下条件をすべて満たすときが交差となる
	//
	//    P1Q1 x P1P2 と P1Q1 x P1Q2 が異符号
	//                かつ
	//    P2Q2 x P2P1 と P2Q2 x P2Q1 が異符号
	//
	if (Cross(vector3, startPoint4 - startPoint3) * Cross(vector3, endPoint4 - startPoint3) < 0 &&
		Cross(vector4, startPoint3 - startPoint4) * Cross(vector4, endPoint3 - startPoint4) < 0)
		return true;

	//プレイヤーの左右足元（２点）からの移動ベクトルと移動後パドルの上辺が交差してれば当たってる

	return false;
}
//実体化してないパドルとの判定
bool HitJudgeManager::HitJudge_notMaterialization(BoxCollider* player, BoxCollider* paddle)
{
	//プレイヤーの左右足元（２点）からの移動ベクトルとパドルの上辺の左右（２点）からの移動ベクトルが交差していれば当たってる　（最大４回判定）

	return false;
}