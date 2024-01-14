#include "Enemy1.hpp"

void Enemy1::__fire(Vector2 playerPos, Vector2 w)
{
	const Vector2 pos = getPosition();
	const Vector2 motionRectSize = __getMotionRectSize();

	spEnemyShot shot(new EnemyShot());

	__setShotWait(120);

	const Vector2 vector = pos + motionRectSize * 0.5;
	shot->Fire(playerPos, vector);

	//�U��SE�𗬂�
	// m_Audio->Play(Audio_EnemyAttack, false);
	__getShotArray().push_back(shot);
}

Enemy1::Enemy1()
	: Enemy()
	, _shotWait(0)
{
}

void Enemy1::Attack(Vector2 playerPos, Vector2 w)
{
	const Vector2 pos = getPosition();
	const Vector2 motionRectSize = __getMotionRectSize();

	//�v���C���[�̕����Ɍ�����
	const bool isReverse = (pos.x + motionRectSize.x * 0.5f < playerPos.x);
	setReverse(!isReverse);

	//�X�N���[����
	const Vector2 screenSize = getScreenSize() + w;

	//�G����ʂɉf���Ă��邩�ǂ���
	const bool isInScreen = (pos.x + motionRectSize.x > w.x && screenSize.x > pos.x);
	__setIsInScreen(isInScreen);

	const bool isFire = (getDamageWait() <= 0 && __getShotWait() <= 0 && __isInScreen());
	if (isFire) __fire(playerPos, w);
	else __updateShotWait(-1);

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spEnemyShot work = __getShotArray()[cnt];

		if (!work->isActive()) continue;

		work->Update(screenSize);
	}
}