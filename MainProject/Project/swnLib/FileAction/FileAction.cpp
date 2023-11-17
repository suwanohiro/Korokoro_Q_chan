#include "FileAction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

std::string FileAction::ConvertFileLink(const std::string& relativePath) {
    char path[MAX_PATH];
    DWORD length = GetModuleFileNameA(NULL, path, MAX_PATH);

    if (length == 0) return std::string("");

    std::string programPath(path, length);

    size_t found = programPath.find_last_of("\\/");
    std::string programDirectory = programPath.substr(0, found + 1);

    std::string fullPath = programDirectory + relativePath;

    // std::string を LPSTR に変換
    int size = fullPath.length() + 1;
    LPSTR lpAbsolutePath = new char[size];
    strcpy_s(lpAbsolutePath, size, fullPath.c_str());

    std::string result(lpAbsolutePath);
    delete[] lpAbsolutePath;

    return result;
}

std::string FileAction::Read(const std::string& currentFilePath) {
    // ファイルパスを変換
    // ファイルを開いて読み込み、内容を文字列として返す
    std::string path = ConvertFileLink(currentFilePath);
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

std::vector<std::vector<std::string>> FileAction::ReadCSV(const std::string& currentFilePath) {
    // 指定されたCSVファイルを読み込む
    // 読み込んだデータを2次元ベクターに格納して返す
    std::string textData = Read(currentFilePath);
    static std::vector<std::vector<std::string>> result;
    std::istringstream iss(textData);
    std::string line;

    while (std::getline(iss, line)) {
        std::vector<std::string> work;
        std::istringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            work.push_back(cell);
        }

        result.push_back(work);
    }

    return result;
}

void FileAction::Write(const std::string& currentFilePath, const std::string& writestring, const std::string& fileReadMode) {
    // ファイルパスを変換
    // ファイルを開いて指定されたモードで書き込む
    std::string path = ConvertFileLink(currentFilePath);
    std::ios_base::openmode mode = (fileReadMode == "a") ? std::ios::app : std::ios::out | std::ios::binary;
    std::ofstream file(path, mode);
    file << writestring;
    file.close();
}

void FileAction::WriteAdd(const std::string& currentFilePath, const std::string& writestring) {
    // 追記モードでファイルに書き込む
    Write(currentFilePath, writestring, "a");
}

void FileAction::WriteNew(const std::string& currentFilePath, const std::string& writestring) {
    // 新規書き込みモードでファイルに書き込む
    Write(currentFilePath, writestring, "w");
}

void FileAction::Clear(const std::string& currentFilePath) {
    // ファイルをクリアするために空の文字列でファイルに書き込む
    WriteNew(currentFilePath, "");
}
