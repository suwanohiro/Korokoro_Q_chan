#pragma once
#include "Mof.h"

#include <regex>

class StringAction
{
public:
	static Vector2 getStringSize(LPCMofChar pText);
	static Vector2 getStringSize(LPCMofChar pText, CFont* font);

	/// <summary>
	/// 文字列を一定数で区切り配列化する
	/// </summary>
	/// <param name="baseStr">変換したい文字列</param>
	/// <param name="step">間隔文字数</param>
	/// <returns>変換した配列データ</returns>
	static std::vector<std::string> split(std::string baseStr, int step);

	/// <summary>
	/// 文字列を特定の文字で区切り配列化する
	/// </summary>
	/// <param name="baseStr">変換したい文字列</param>
	/// <param name="cutStr">区切りたい文字</param>
	/// <returns>変換した配列データ</returns>
	static std::vector<std::string> split(std::string baseStr, std::string cutStr);

	/// <summary>
	/// 文字列を正規表現を使用して配列化する
	/// </summary>
	/// <param name="baseStr">変換したい文字列</param>
	/// <param name="regex">正規表現</param>
	/// <returns>変換した配列データ</returns>
	static std::vector<std::string> split(std::string baseStr, std::regex regex);
};

