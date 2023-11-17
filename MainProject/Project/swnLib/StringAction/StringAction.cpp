#include "StringAction.h"

Vector2 StringAction::getStringSize(LPCMofChar pText)
{
	return getStringSize(pText, NULL);
}

Vector2 StringAction::getStringSize(LPCMofChar pText, CFont* font)
{
	Vector2 result;
	CRectangle textRect(0, 0, 0, 0);
	if (font != NULL) font->CalculateStringRect(0, 0, pText, textRect);
	else CGraphicsUtilities::CalculateStringRect(0, 0, pText, textRect);

	result.x = textRect.Right - textRect.Left;
	result.y = textRect.Bottom - textRect.Top;

	return result;
}

std::vector<std::string> StringAction::split(std::string baseStr, int step)
{
	std::vector<std::string> result;
	const int length = baseStr.length();

	for (int cnt = 0; cnt < length; cnt += step) {
		std::shared_ptr<char> substr(new char[step + 1]);
		std::strncpy(substr.get(), baseStr.c_str() + cnt, step);
		substr.get()[step] = '\0';
		result.push_back(std::string(substr.get()));
	}

	return result;
}

std::vector<std::string> StringAction::split(std::string baseStr, std::string cutStr)
{
	std::vector<std::string> result;

	unsigned int start = 0;
	unsigned int end = baseStr.find(cutStr);

	while (end != std::string::npos) {
		result.push_back(baseStr.substr(start, end - start));
		start = end + cutStr.length();
		end = baseStr.find(cutStr, start);
	}

	result.push_back(baseStr.substr(start, end));
	return std::vector<std::string>();
}

std::vector<std::string> StringAction::split(std::string baseStr, std::regex regex)
{
	std::vector<std::string> result;

	std::sregex_token_iterator iter(baseStr.begin(), baseStr.end(), regex, -1);
	std::sregex_token_iterator end;

	for (; iter != end; ++iter) {
		result.push_back(*iter);
	}

	return std::vector<std::string>();
}
