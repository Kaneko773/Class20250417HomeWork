#pragma once

const int ScreenHeight = 640;
const int ScreenWidth = 480;


const int PlayerPictureHeight = 400;
const int PlayerPictureWidth = 358;

const int PaddleSizeWidth = 100;
const int PaddleSizeHeight = 10;

const float DeadZoneHeight = 50;//トゲトゲの高さ//調整可

//パドルの速度（非実体化時）
const float PaddleSpeed = 100.0f;
//パドルの初速度（実体化時）
const float InitialVelocity = 2.0f;
//パドルの加速度（実体化時）
const float PaddleAcceleration = 0.5f;

// プレイヤーの速度( 1秒間に移動するドット数 )、横移動用
//float add = 200.0f;

//プレイヤーの重力加速度
const float GravityAcceleration = 2;