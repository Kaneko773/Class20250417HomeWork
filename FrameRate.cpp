#include "DxLib.h"
#include "FrameRate.h"

//�σt���[�����[�g�p
LONGLONG NowTime = GetNowHiPerformanceCount();
// �V�X�e�����Ԃ��擾���Ă���
LONGLONG Time = GetNowHiPerformanceCount();
// �ŏ��̌o�ߎ��Ԃ͉��� 0.000001f �b�ɂ��Ă���
float DeltaTime = 0.000001f;

void FrameRate::FrameRateUpdate()
{
	// ���݂̃V�X�e�����Ԃ��擾
	NowTime = GetNowHiPerformanceCount();
	// �O��擾�������Ԃ���̌o�ߎ��Ԃ�b�ɕϊ����ăZ�b�g
	// ( GetNowHiPerformanceCount �Ŏ擾�ł���l�̓}�C�N���b�P�ʂȂ̂� 1000000 �Ŋ��邱�Ƃŕb�P�ʂɂȂ� )
	DeltaTime = (NowTime - Time) / 1000000.0f;
	// ����擾�������Ԃ�ۑ�
	Time = NowTime;
}

float FrameRate::Get_Deltatime() {
	return DeltaTime;
}