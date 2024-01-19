#include "Countdown.h"

/*
�R���X�g���N�^
*/
Countdown::Countdown()
	: progressTime(0)
	, timeLimit(0)
	, remaining(0)
	, isProcess(false)
	, isRemaining(true)
{
}
/*
�f�X�g���N�^
*/
Countdown::~Countdown()
{
}

void Countdown::Initialize()
{
	progressTime = 0;
	timeLimit = 0;
	remaining = 0;
	isProcess = false;
	isRemaining = true;
}

/*
�J�E���g�_�E������
*/
void Countdown::Update()
{
	// ���s���łȂ���Ώ������Ȃ�
	if (!isProcess) return;

	progressTime += CUtilities::GetFrameSecond();

	// �c�莞�Ԃ��v�Z����
	remaining = timeLimit - progressTime;

	if (remaining < 0) {
		remaining = 0;
		isRemaining = false;
	}
}

void Countdown::Render()
{
	CGraphicsUtilities::RenderString(850, 40, "�c��%2.2f�b", remaining);
}
