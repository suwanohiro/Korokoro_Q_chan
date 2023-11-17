#pragma once

#include <string>
#include <vector>

class FileAction {
public:
    // ファイルパスの変換を行う関数
    static std::string ConvertFileLink(const std::string& currentFilePath);

    // ファイルの読み込みを行う関数
    static std::string Read(const std::string& currentFilePath);

    // CSVファイルの読み込みを行う関数
    static std::vector<std::vector<std::string>> ReadCSV(const std::string& currentFilePath);

    // ファイルの書き込みを行う関数
    static void Write(const std::string& currentFilePath, const std::string& writestring, const std::string& fileReadMode);

    // ファイルに追記する関数
    static void WriteAdd(const std::string& currentFilePath, const std::string& writestring);

    // ファイルに新規書き込みする関数
    static void WriteNew(const std::string& currentFilePath, const std::string& writestring);

    // ファイルをクリアする関数
    static void Clear(const std::string& currentFilePath);
};
