#pragma once


class CGravity {
private:

	///<summary>
	///�d�͐��l
	///</summary>
	float m_Gravity;

public:
	CGravity();
	~CGravity();

	///<summary>
	///�d��
	///</summary>
	void Gravity(float& sy);
};