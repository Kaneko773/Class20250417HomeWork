#pragma once

const int ScreenHeight = 640;
const int ScreenWidth = 480;


const int PlayerPictureHeight = 400;
const int PlayerPictureWidth = 358;

const int PaddleSizeWidth = 100;
const int PaddleSizeHeight = 10;

const float DeadZoneHeight = 50;//�g�Q�g�Q�̍���//������

//�p�h���̑��x�i����̉����j
const float PaddleSpeed = 100.0f;
//�p�h���̏����x�i���̉����j
const float InitialVelocity = 2.0f;
//�p�h���̉����x�i���̉����j
const float PaddleAcceleration = 0.5f;

// �v���C���[�̑��x( 1�b�ԂɈړ�����h�b�g�� )�A���ړ��p
//float add = 200.0f;

//�v���C���[�̏d�͉����x
const float GravityAcceleration = 2;