#pragma once


class CGravity {
private:

	///<summary>
	///重力数値
	///</summary>
	float m_Gravity;

public:
	CGravity();
	~CGravity();

	///<summary>
	///重力
	///</summary>
	void Gravity(float& sy);
};