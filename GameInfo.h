#pragma once

const int PlayerPictureWidth = 300;
const int PlayerPictureHeight = 300;
const float ReductionMag = 4;//画像の縮小倍率


//調整可能

//画面サイズ
const int ScreenWidth = 480;
const int ScreenHeight = 640;
//トゲトゲの高さ
const float DeadZoneHeight = ScreenHeight * 0.08f;
//プレイヤーのジャンプ力
const float PlayerJumpPower = 1.5f;
//プレイヤーの重力加速度
const float GravityAcceleration = 15;
//パドルの速度の最低値（非実体化時）
const float PaddleSpeed_LowestValue = 600.0f;
//パドルの加速度（実体化時）
const float PaddleAcceleration = 1.0f;
//パドルの大きさ
const int PaddleSizeWidth = 100;
const int PaddleSizeHeight = 10;
//パドルを生成する高さ
const int Max_PaddleCreateHeight = 150;
const int Min_PaddleCreateHeight = -80;
//パドル生成の間隔
const float PaddleCreateCoolTime = 0.01f;