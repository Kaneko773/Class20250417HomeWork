#pragma once

const int PlayerPictureWidth = 300;
const int PlayerPictureHeight = 300;
const float ReductionMag = 4;//�摜�̏k���{��


//�����\

//��ʃT�C�Y
const int ScreenWidth = 480;
const int ScreenHeight = 640;
//�g�Q�g�Q�̍���
const float DeadZoneHeight = ScreenHeight * 0.08f;
//�v���C���[�̃W�����v��
const float PlayerJumpPower = 1.5f;
//�v���C���[�̏d�͉����x
const float GravityAcceleration = 15;
//�p�h���̑��x�̍Œ�l�i����̉����j
const float PaddleSpeed_LowestValue = 600.0f;
//�p�h���̉����x�i���̉����j
const float PaddleAcceleration = 1.0f;
//�p�h���̑傫��
const int PaddleSizeWidth = 100;
const int PaddleSizeHeight = 10;
//�p�h���𐶐����鍂��
const int Max_PaddleCreateHeight = 150;
const int Min_PaddleCreateHeight = -80;
//�p�h�������̊Ԋu
const float PaddleCreateCoolTime = 0.01f;