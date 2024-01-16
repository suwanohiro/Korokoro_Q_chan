#include "Enemy1.hpp"

void Enemy1::__fire(Vector2 playerPos)
{
	const Vector2 pos = getPosition();
	const Vector2 motionRectSize = __getMotionRectSize();

	spEnemyShot shot(new EnemyShot());
	shot->Initialize(playerPos);

	__setShotWait(120);

	const Vector2 vector = pos + motionRectSize * 0.5;
	shot->Fire(playerPos, vector);

	shot->setTexture(__getShotspTexture());

	//攻撃SEを流す
	__getAudioManager()->play(AudioTrack::SE_Enemy_Attack);

	__getShotArray().push_back(shot);
}

Enemy1::Enemy1(spAudioManager audioManager, spEffectManager effectManager)
	: Enemy(audioManager, effectManager)
{
}

void Enemy1::Attack(Vector2 playerPos, Vector2 w)
{
	const Vector2 pos = getPosition();
	const Vector2 motionRectSize = __getMotionRectSize();

	//プレイヤーの方向に向ける
	const bool isReverse = (pos.x + motionRectSize.x * 0.5f < playerPos.x);
	setReverse(!isReverse);

	//スクリーン幅
	const Vector2 screenSize = __getScreenSize() + w;

	//敵が画面に映っているかどうか
	const bool isInScreen = (pos.x + motionRectSize.x > w.x && screenSize.x > pos.x);
	__isInScreen(isInScreen);

	const bool isFire = (getDamageWait() <= 0 && __getShotWait() <= 0 && __isInScreen());
	if (isFire) __fire(playerPos);
	else __updateShotWait(-1);

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spEnemyShot work = __getShotArray()[cnt];

		if (!work->isActive()) continue;

		work->FixedUpdate(screenSize);
		work->Update();
		work->LateUpdate();
	}
}
