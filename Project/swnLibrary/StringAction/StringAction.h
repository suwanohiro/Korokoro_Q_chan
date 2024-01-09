#pragma once
#include "Mof.h"

#include <vector>
#include <regex>

class StringAction
{
public:
	/// <summary>
	/// 文字列のサイズを取得
	/// </summary>
	/// <param name="pText"></param>
	/// <returns></returns>
	static Vector2 GetStringSize(LPCMofChar pText);
	static Vector2 GetStringSize(LPCMofChar pText, CFont* font);

	/// <summary>
	/// 正規表現を使用して配列に変換
	/// </summary>
	/// <param name="str">変換したい文字列</param>
	/// <param name="step">間隔文字数</param>
	static std::vector<std::string> Split(std::string str, int step);

	/// <summary>
	/// 正規表現を使用して配列に変換
	/// </summary>
	/// <param name="str">変換したい文字列</param>
	/// <param name="cutStr">切り取り文字列</param>
	static std::vector<std::string> Split(std::string str, std::string cutStr);

	/// <summary>
	/// 正規表現を使用して配列に変換
	/// </summary>
	/// <param name="str">変換したい文字列</param>
	/// <param name="regex">対象となる正規表現</param>
	static std::vector<std::string> Split(std::string str, std::regex regex);
};

