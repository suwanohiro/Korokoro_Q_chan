#pragma once

#include "Item.h"

class ItemHeel : public CItem
{
private:

public:
	void Initialize(Vector2 pos, CTexture* texture);					//������
	void Update(void);								//�X�V
	void CollisionStage(float oy);					//�X�e�[�W�ƏՓ˂����ۂ̕␳����
	void Render(void);								//�`��
	void Release(void);								//���

	bool GetShow(void) { return m_bShow; }			//�A�C�e���̕\���L��
	void SetShow(bool flg) { m_bShow = flg; }		// �\����Ԃ�ݒ肷��
	CRectangle GetRect();							//�������`
};
