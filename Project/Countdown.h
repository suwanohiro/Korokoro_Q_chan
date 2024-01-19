#pragma once

#include	"Mof.h"


class Countdown
{
private:
	int timeLimit;//��������
	float remaining;//�c�莞��
	float progressTime;//�o�ߎ���
	bool isProcess;//���s�����ǂ���
	bool isRemaining;//�c�莞�Ԃ����邩�ǂ���

public:
	Countdown();
	~Countdown();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �J�E���g�_�E���X�^�[�g
	/// </summary>
	void Start() { if (!isProcess) isProcess = true; }

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// �J�E���g�_�E�����Ԃ�ݒ肷��
	/// </summary>
	/// <param name="cnt"></param>
	void SetCountdown(int cnt) { 
		// ���s���Ȃ�ύX�����Ȃ�
		if (isProcess) return;

		timeLimit = cnt;
	}

	/// <summary>
	/// �J�E���g�_�E�����Ԃ��擾����
	/// </summary>
	/// <returns></returns>
	float GetLimit() const { return timeLimit; }

	/// <summary>
	/// �c�莞�Ԃ����邩���擾����
	/// </summary>
	/// <returns>�c�莞�ԃt���O true:�c�莞�Ԃ����� false:�c�莞�Ԃ��Ȃ�</returns>
	float GetRemaining() {
		return isRemaining;
	}
};