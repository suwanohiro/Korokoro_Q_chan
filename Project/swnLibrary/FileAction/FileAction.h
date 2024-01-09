#pragma once

#include <string>
#include <vector>
#include "./json.hpp"


using JSON = nlohmann::json;
using CSVData = std::vector<std::vector<std::string>>;

class FileAction {
public:
    /// <summary>
    /// 実行ファイルからの相対パスを絶対パスに変更する
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    /// <returns></returns>
    static std::string ConvertFileLink(const std::string& currentFilePath);

    /// <summary>
    /// ファイルを読み込む
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    /// <returns>読み込んだ文字列データ</returns>
    static std::string Read(const std::string& currentFilePath);

    /// <summary>
    /// CSVファイルを読み取り2次元配列を返す
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    /// <returns>CSVデータの2次元配列</returns>
    static CSVData ReadCSV(const std::string& currentFilePath);

    /// <summary>
    /// JSONファイルを読み込む
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    /// <returns>JSONデータ</returns>
    static JSON ReadJSON(const std::string& currentFilePath);

    /// <summary>
    /// データを書き込む
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    /// <param name="writestring">書き込む文字列</param>
    /// <param name="fileReadMode">書き込みモード</param>
    static void Write(const std::string& currentFilePath, const std::string& writestring, const std::string& fileReadMode);

    /// <summary>
    /// データを書き込む (追記)
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    /// <param name="writestring">書き込む文字列</param>
    static void WriteAdd(const std::string& currentFilePath, const std::string& writestring);

    /// <summary>
    /// データを書き込む (上書き)
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    /// <param name="writestring">書き込む文字列</param>
    static void WriteNew(const std::string& currentFilePath, const std::string& writestring);

    /// <summary>
    /// データを削除する
    /// </summary>
    /// <param name="currentFilePath">実行ファイルからの相対パス</param>
    static void Clear(const std::string& currentFilePath);
};
