/*****************************************************************
@file
@brief Входной файл проекта
Здесь описывается основной алгоритм программы, и находится точка 
входа
*****************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <locale>
#include <errno.h>
#include "coreFunctions.h"
#include "enums.h"
#include <io.h>
#include <fcntl.h>

using namespace std;
using namespace chrono;

const string RESULT_FOLDER_NAME = "results_of_";

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printHeader();

    double time;
    string inpFilePath, outFolderPath, outResultFilePath, outAnalysisFilePath;
    wstring inp, stat;
    vector<wstring> words;
    
    //Получаем пути до файлов с которыми будем работать
    FileData InputFileData = getFileData();
    inpFilePath = InputFileData.path + InputFileData.name + "." + InputFileData.extension;
    outFolderPath = InputFileData.path + RESULT_FOLDER_NAME + InputFileData.name + "." + InputFileData.extension;
    outResultFilePath = outFolderPath + "/result.txt";
    outAnalysisFilePath = outFolderPath + "/analysis.txt";

    //Открываем файл входных данных, создаем папку для хранения результатов и файлы результатов
    wifstream InputFile(inpFilePath);
    if (InputFile.is_open()) log(L"Файл входных данных \"" + to_wstring(inpFilePath) + L"\" успешно открыт");
    else {
        log(L"Не получилось открыть файл входных данных \"" + to_wstring(inpFilePath) + L"\"", ERR);
        InputFile.close();
        return 0;
    }
     
    //Создаем папку для хранения результатов выполнения (файла результата и анализа)
    if (_mkdir(outFolderPath.c_str()) == 0) log(L"Папка для хранения результатов выполнения успешно создана по адресу \"" + to_wstring(outFolderPath) + L"\"");
    else if (errno == EEXIST) log(L"Папка для хранения результатов выполнения уже существует по адресу \"" + to_wstring(outFolderPath) + L"\"", WARN);
    else {
        log(L"Не удалось создать папку для хранения результатов выполнения по адресу \"" + to_wstring(outFolderPath) + L"\"", ERR);
        InputFile.close();
        return 0;
    }

    //Создаем результирующий файл
    wofstream ResultFile(outResultFilePath);
    if (ResultFile.is_open()) log(L"Файл результата работы успешно создан по адресу \"" + to_wstring(outResultFilePath) + L"\"");
    else {
        log(L"Не удалось создать файл результата по адресу \"" + to_wstring(outResultFilePath) + L"\"", ERR);
        InputFile.close();
        ResultFile.close();
        return 0;
    }

    //Создаем файл аналитики/статистики/анализа
    wofstream AnalysisFile(outAnalysisFilePath);
    if (AnalysisFile.is_open()) log(L"Файл аналитики успешно создан по адресу \"" + to_wstring(outAnalysisFilePath) + L"\"");
    else {
        log(L"Не удалось создать файл аналитики по адресу \"" + to_wstring(outAnalysisFilePath) + L"\"", ERR);
        InputFile.close();
        AnalysisFile.close();
        ResultFile.close();
        return 0;
    }

    //Получаем информацию из файла ввода в виде строки
    inp = readFromFile(InputFile);
    //Разбиваем полученную строку на вектор слов
    words = split(inp);
    //Производим сортировку Шелла и замеряем время ее выполнения
    time = benchmark(words, shell);
    //Записываем результаты в файлы анализа и статистики
    writeIntoResultFIle(words, ResultFile);
    writeIntoStatisticFIle(inp, words.size(), time, words, AnalysisFile);


    InputFile.close();
    ResultFile.close();
    AnalysisFile.close();

	return 0;
}