/******************************************************************
@file
@brief ������������ ���� ��������
����� ����������� ���������, ������������ � �������
******************************************************************/
#pragma once

#include <string>

using namespace std;

/// ��������� ���������� �� ����� �����
struct FileData {
    string name; /// �������� ����� (��� ����������)
    string path; /// ���� �� �������� ��� ���������� ����
    string extension; /// ���������� �����
};