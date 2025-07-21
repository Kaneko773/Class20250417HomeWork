#pragma once

const int PlayerPictureHeight = 300;
const int PlayerPictureWidth = 300;
const float ReductionMag = 4;//画像の縮小倍率

// プレイヤーの速度( 1秒間に移動するドット数 )、横移動用
//float add = 200.0f;

//調整可能

//画面サイズ
const int ScreenHeight = 640;
const int ScreenWidth = 480;
//トゲトゲの高さ
const float DeadZoneHeight = ScreenHeight * 0.08f;
//プレイヤーのジャンプ力
const float PlayerJumpPower = 1.5f;//0.6
//プレイヤーの重力加速度
const float GravityAcceleration = 15;//2
//パドルの速度の最低値（非実体化時）
const float PaddleSpeed_LowestValue = 600.0f;
//パドルの加速度（実体化時）
const float PaddleAcceleration = 0.5f;
//パドルの大きさ
const int PaddleSizeWidth = 100;
const int PaddleSizeHeight = 10;