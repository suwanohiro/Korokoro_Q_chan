#include "StringAction.h"

Vector2 StringAction::GetStringSize(LPCMofChar pText)
{
	LPCMofChar a = "";

	const char* aaa = a;

	return GetStringSize(pText, NULL);
}

Vector2 StringAction::GetStringSize(LPCMofChar pText, CFont* font)
{
	Vector2 result;
	CRectangle textRect(0, 0, 0, 0);
	if (font != NULL) font->CalculateStringRect(0, 0, pText, textRect);
	else CGraphicsUtilities::CalculateStringRect(0, 0, pText, textRect);

	result.x = textRect.Right - textRect.Left;
	result.y = textRect.Bottom - textRect.Top;

	return result;
}

std::vector<std::string> StringAction::Split(std::string str, int step)
{
	std::vector<std::string> result;
	const int length = str.length();

	for (int cnt = 0; cnt < length; cnt += step) {
		std::shared_ptr<char> substr(new char[step + 1]);
		std::strncpy(substr.get(), str.c_str() + cnt, step);
		substr.get()[step] = '\0';
		result.push_back(std::string(substr.get()));
	}
	return result;
}

std::vector<std::string> StringAction::Split(std::string str, std::string cutStr)
{
	std::vector<std::string> result;

	size_t start = 0;
	size_t end = str.find(cutStr);

	while (end != std::string::npos) {
		result.push_back(str.substr(start, end - start));
		start = end + cutStr.length();
		end = str.find(cutStr, start);
	}

	result.push_back(str.substr(start, end));
	return result;
}

std::vector<std::string> StringAction::Split(std::string str, std::regex regex)
{
	std::vector<std::string> result;

	std::sregex_token_iterator iter(str.begin(), str.end(), regex, -1);
	std::sregex_token_iterator end;

	for (; iter != end; ++iter) {
		result.push_back(*iter);
	}

	return result;
}
