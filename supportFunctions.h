/*****************************************************************
\file
\brief ������������ ���� ��������������� �������
����� ����������� �������, �� ������������ ��������������� � ����� ����� (main),
�� ����������� ��� ������ ������ �������
*****************************************************************/
#pragma once

#include <string>
#include <direct.h>
#include <windows.h>
#include "enums.h"

using namespace std;

/*****************************************************************
������������ ������ ���� string � ������ ���� wstring
\param str ������ ���� string
\return ������ ���� wstring
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
�������� ���� ������ � �������
\param text ���� ������
\param background ���� ����
*****************************************************************/
void SetConsoleColor(ConsoleColor text, ConsoleColor background=Black) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

/*****************************************************************
���������, �������� �� ������ ������������ � �������� �����
��� ��������
\param s ����������� ������
\return true, ���� ������ ������������, � false � ��������� ������
*****************************************************************/
bool isForbiddenNameSymb(wchar_t s) {
    return (s == '>' || s == '<' || s == ':' || s == '"' || s == '|' || s == '?') ? true : false;
}

/*****************************************************************
���������, ���������� �� ���� �� ���������� ����
\param path ����, ��������� � ���� ��� ����� � �����������
\return true, ���� ���� �����������, � false � ��������� ������
*****************************************************************/
bool isFileExist(string path) {
    bool result = false;
    ifstream fin(path);
    if (fin.is_open()) result = true;
    fin.close();
    return result;
}

/*****************************************************************
�������� �������� ������ ������� � ��������
\return �������� ������ ������� � ��������, ��� -1, ���� �� 
������� ��� ��������
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
�������� ��� ��������, � ������� ����������� ���������
\return ������ � ���� �� �������� ��������
****************************************************************/
string getCurrentPath() {
    char buff[260];
    string result(_getcwd(buff, sizeof(buff)));
    return result;
}

/*****************************************************************
�������� ���������� ����������� ����� �����
\param name ��� ����� � �����������
\return ����������, ��� "-1", ���� ��� �� �������� ����������
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
�����������, �������� �� ���������� ������ ��������-�������������
\param c ������ � ��������� ANSI
\return true - ���� �������� false - ���� �� ��������
*****************************************************************/
bool isLetter(wchar_t c) {
    return ((c >= 192 && c <= 255) || c == 168 || c == 184) ? true : false;
}