
#pragma once

#include <fstream>
#include <string>
#include <regex>
#include <locale>
#include <vector>
#include <chrono>
#include "supportFunctions.h"
#include "structs.h"
#include "enums.h"

using namespace std;
using namespace chrono;


void log(wstring s, ConsoleFormats mode=LOG, bool br=true) {
    SetConsoleColor(White);
    if (br) wcout << "\n";
    wcout << L"[";
    if (mode == ERR) {
        SetConsoleColor(LightRed);
        wcout << L"ERROR";
        s = L"  " + s;
    }
    else if (mode == WARN) {
        SetConsoleColor(Yellow);
        wcout << L"WARNING";
    }
    else if (mode == DC) {
        SetConsoleColor(DarkGray);
        wcout << L"OUTPUT";
        s = L" "+s;
    }
    else if (mode == INP) {
        SetConsoleColor(DarkGray);
        wcout << L"INPUT";
        s = L"  " + s;
        s += L": ";
    }
    else {
        SetConsoleColor(LightGreen);
        wcout << L"LOG";
        s = L"    " + s;
    }
    SetConsoleColor(White);
    wcout << L"] ";
    SetConsoleColor(DarkGray);
    wcout << s;
    SetConsoleColor(LightGray);
}

void printHeader() {
    wstring c = L"*";
    const int N = 3;
    int i,j, w = getConsoleWidth();
    wstring strs[N] = {L"ГУАП 2022",
                      L"Задание по учебной практике, Коновалов Д.В., Группа 5138",
                      L"Вариант 10"};
    if (w == -1) {
        log(L"Шапка не отображена. Не удалось получить ширину окна консоли", WARN);
        return;
    }

    for (i = 0; i < N; i++) {
        if (strs[i].length() > w-6) {
            log(L"Шапка не отображена. Ширина шапки превышает ширину консоли", WARN);
            return;
        }
    }

    for (i = 0; i < w; i++) {  wcout << c; }
    cout << "\n";

    for (i = 0; i < N; i++) {
        wcout << c << c << c;
        for (j = 0; j < (w-6 - strs[i].length()) / 2; j++) { wcout << " "; }
        wcout << strs[i];
        if (strs[i].length() % 2 != 0) wcout << " ";
        for (j = 0; j < (w-6 - strs[i].length()) / 2; j++) { wcout << " "; }
        wcout << c << c << c <<"\n";
    }
    for (i = 0; i < w; i++) { wcout << c; }
}


FileData getFileData() {
    bool err = false, wrn = false, needName = true;
    char s;
    int i, n = 0;
    string tname = "", name = "", path = "", tpath = "", folder = "", ext = "";
    FileData result;

    //Запрашиваем данные до тех пор, пока пользователь не введет корректные
    do {
        log(L"Введите путь до обрабатываемого файла",DC);
        log(L"Путь", INP);
        cin >> tpath;

        for (i = 0; i < tpath.length(); i++) {
            s = tpath[i];

            //Проверка на недопустимые символы
            if (isForbiddenNameSymb(s)) {
                err = true;
                wrn = true;
                log(L"Введённый путь содержит недопустимые символы (> < : \" | ?)", ERR, 0);
                break;
            }
            else err = false;

            //В folder храним название последнего каталога, который может оказаться именем файла
            if (s == '/' || s == '\\') {
                folder = "";
                n++;
            }
            else folder += s;
        }

        //Если последний каталог имеет расширение - признаем его именем файла и соответственно обрабатываем
        if (getFIleExtention(folder) != "-1") {
            ext = getFIleExtention(folder);

            for (i = 0; i < folder.length() - ext.length() - 1; i++) {
                name += folder[i];
            }
            needName = false;

            //Если путь состоит только из имени файла то на всякий случай за путь принимаем путь до исполняемого файла программы
            if (n == 0) {
                path = getCurrentPath();
                if (path == "0") {
                    err = true;
                    wrn = true;
                    log(L"Ошибка получения пути текущего каталога", ERR, err ? 1 : 0);
                }
            }
            else {
                for (i = 0; i < tpath.length() - name.length() - ext.length() - 1; i++) {
                    path += tpath[i];
                }
            }
        }
        else {
            for (i = 0; i < tpath.length() - name.length() - ext.length(); i++) {
                path += tpath[i];
            }
        }
        
        //На всякий случай приводим все слеши в пути к единому виду
        for (i = 0; i < path.length(); i++) {
            if (path[i] == '/') path[i] = '\\';
        }

        //Если пользователь не дописал в конце пути слещ - дописываем
        if (path[path.length() - 1] != '\\') path += "\\";

    } while (err);

    //Если имя не было получено в составе пути - получаем его, и будем запрашивать, пока не будут введены корректные данные
    if (needName) {
        do {
            log(L"Введите имя обрабатываемого файла", DC, wrn ? 1 : 0);
            log(L"Имя", INP);
            cin >> tname;

            wrn = false;

            //Проверка на недопустимые символы
            for (i = 0; i < tname.length(); i++) {
                s = tname[i];

                if (isForbiddenNameSymb(s) || s == '\\' || s == '/') {
                    err = true;
                    log(L"Введённое содержит недопустимые символы (> < : \" | ? / \\)", ERR, 0);
                    break;
                }
                else err = false;
            }

            //Если имя содержит расширение - оставляем его как есть, если не содержит - принимаем за расширение .txt
            if (getFIleExtention(tname) != "-1") {
                ext = getFIleExtention(tname);
                for (i = 0; i < tname.length() - ext.length() - 1; i++) {
                    name += tname[i];
                }
            }
            else {
                name = tname;
                ext = "txt";
                wrn = true;
                log(L"Введённое имя файла не содержит расширение. По умолчанию было установлено расширение txt", WARN, err?1:0);
            }
        } while (err);
    }

    //Проверяем файл на существование, и в случае, если его нет - рекурсивно запрашиваем новые данные
    if (!isFileExist(path + name + "." + ext)) {
        log(L"Файл не найден по пути \"" + to_wstring(path) + to_wstring(name) + L"." + to_wstring(ext) + L"\"", ERR, err||wrn ? 1 : 0);
        result = getFileData();
    }
    else {
        log(L"Файл \"" + to_wstring(path) + to_wstring(name) + L"." + to_wstring(ext) + L"\" обнаружен",LOG, wrn ? 1 : 0);
        result.name = name;
        result.path = path;
        result.extension = ext;
    }

    return result;
}


wstring readFromFile(wifstream &InputFile) {
    wstring res = L"";
    wchar_t c;

    c = InputFile.get();
    res = c;
    while (!InputFile.eof()) {
        c = InputFile.get();
        res += c;
    }
    log(L"Информация из входного файла успешно получена");
    return res;
}   


void writeIntoResultFIle(vector<wstring> A, wofstream &OutputFile) {
    for (int i = 0; i < A.size(); i++) {
        OutputFile << A[i] << " ";
    }
    log(L"Отсортированный массив успешно записан в файл результата");
}


void writeIntoStatisticFIle(wstring txt, int n, double t, vector<wstring> a, wofstream& OutputFile) {
    OutputFile << "Введенный текст: " << txt << "\n";
    OutputFile << "Вариант 10: Кириллица; По алфавиту; По возрастанию; Игнорировать числа; Сортировка Шелла;\n";
    OutputFile << "Количесво слов: " << n << "\n";
    OutputFile << "Время сортировки: " << t << "s\n";
    OutputFile << "Статистика (количество слов на каждую букву алфавита):\n";

    vector<int> stat;
    wstring res = L"";
    int i;
    wchar_t c;

    for (i = 0; i < 66; i++)  stat.push_back(0);

    for (i = 0; i < a.size(); i++) {
        c = a[i][0];
        if (c == 168) stat[6]++;
        else if (c == 184) stat[39]++;
        else stat[c - 160 - 32]++;
    }

    for (i = 0; i < 66; i++) {
        wchar_t t = i + 160 + 32;
        OutputFile << t;
        OutputFile << L" - " << to_wstring(stat[i]) << L"\n";
    }

    log(L"Статистика успешно записана в файл статистики");
}


vector<wstring> split(wstring str) {
    vector<wstring> res;
    wstring word = L"";

    for (int i = 0; i < str.length(); i++) {
        wchar_t c = str[i];

        if (isLetter(c)) {
            word += c;
        }
        else if(word != L"") {
            res.push_back(word);
            word = L"";
        }
    }
    log(L"Строка успешно разбита на массив слов, состоящих из кириллических символов");
    return res;
}

void shell(vector<wstring>& A) {
    int i, j, n = A.size(), d = n / 2;
    wstring t;

    while (d > 0) {
        for (i = 0; i < n - d; i++) {
            j = i;
            while (j >= 0 && A[j] > A[j + d]) {
                t = A[j];
                A[j] = A[j + d];
                A[j + d] = t;
                j--;
            }
        }
        d = d / 2;
    }
}


double benchmark(vector<wstring>& a, void (*f)(vector<wstring>&)) {
    system_clock::time_point start = system_clock::now();
    f(a);
    system_clock::time_point end = system_clock::now();
    duration<double> sec = end - start;

    log(L"Массив слов отсортирован за " + to_wstring(sec.count()));
    return sec.count();
}