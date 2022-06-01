/*****************************************************************
\file
\brief Заголовочный файл вспомогательных функций
Здесь описываются функции, не используемые непосредственно в точке входа (main),
но необходимые для работы других функций
*****************************************************************/
#pragma once

#include <string>
#include <direct.h>
#include <windows.h>
#include "enums.h"

using namespace std;

/*****************************************************************
Конвертирует строку типа string в строку типа wstring
\param str Строка типа string
\return Строка типа wstring
*****************************************************************/
wstring to_wstring(const string& str) {
    const locale& loc = locale();
    vector<wchar_t> buf(str.size());
    use_facet<ctype<wchar_t>>(loc).widen(str.data(),
        str.data() + str.size(),
        buf.data());
    return wstring(buf.data(), buf.size());
}

/*****************************************************************
Изменяет цвет текста в консоли
\param text Цвет текста
\param background Цвет фона
*****************************************************************/
void SetConsoleColor(ConsoleColor text, ConsoleColor background=Black) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

/*****************************************************************
Проверяет, является ли символ недопустимым в названии файла
или каталога
\param s Проверяемый символ
\return true, если символ недопустимый, и false в противном случае
*****************************************************************/
bool isForbiddenNameSymb(wchar_t s) {
    return (s == '>' || s == '<' || s == ':' || s == '"' || s == '|' || s == '?') ? true : false;
}

/*****************************************************************
Проверяет, существует ли файл по указанному пути
\param path Путь, включащий в себя имя файла с расширением
\return true, если файл слуществует, и false в противном случае
*****************************************************************/
bool isFileExist(string path) {
    bool result = false;
    ifstream fin(path);
    if (fin.is_open()) result = true;
    fin.close();
    return result;
}

/*****************************************************************
Получает значение ширины консоли в символах
\return значение ширины консоли в символах, или -1, если не 
удалось его получить
*****************************************************************/
int getConsoleWidth() {
    HANDLE hWndConsole;
    if (hWndConsole = GetStdHandle(-12)) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            return consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
        }
    }
    return -1;
}

/****************************************************************
Получает имя каталога, в котором выполняется программа
\return Строку – путь до текущего каталога
****************************************************************/
string getCurrentPath() {
    char buff[260];
    string result(_getcwd(buff, sizeof(buff)));
    return result;
}

/*****************************************************************
Получает расширение переданного имени файла
\param name Имя файла с расширением
\return Расширение, или "-1", если имя не содержит расширения
*****************************************************************/
string getFIleExtention(string name) {
    bool isExtention = false;
    char s;
    string result = "";

    for (int i = 0; i < name.length(); i++) {
        s = name[i];
        if (isExtention) result += s;
        if (s == '.') isExtention = true;
    }

    if (!isExtention) result = "-1";

    return result;
}

/*****************************************************************
Проверяется, является ли переданный символ буквенно-кириллическим
\param c символ в кодировке ANSI
\return true - если является false - если не является
*****************************************************************/
bool isLetter(wchar_t c) {
    return ((c >= 192 && c <= 255) || c == 168 || c == 184) ? true : false;
}