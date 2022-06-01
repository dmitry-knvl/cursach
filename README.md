
# Коновалов 5138

Учебная практика, СПБГУАП, Вариант 10, 2022г.

## Authors

- [@dmitry-knvl](https://www.github.com/dmitry-knvl)


## API Reference


#### to_wstring(str)
Конвертирует строку типа string в строку типа wstring
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `str` | `const string&` | **Required**. Строка типа string |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `wstring` | Строка типа wstring |


#### SetConsoleColor(text, [background])
Изменяет цвет текста в консоли
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `text` | `ConsoleColor` | **Required**. Цвет текста |
| `background` | `ConsoleColor` | Цвет фона |


#### isForbiddenNameSymb(s)
Проверяет, является ли символ недопустимым в названии файла или каталога
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `s` | `wchar_t` | **Required**. Проверяемый символ |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `bool` | true, если символ недопустимый, и false в противном случае |


#### isFileExist(path)
Проверяет, существует ли файл по указанному пути
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `path` | `string` | **Required**. Путь, включащий в себя имя файла с расширением |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `bool` | true, если файл существует, и false в противном случае |


#### getConsoleWidth()
Получает значение ширины консоли в символах
| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `int` | Значение ширины консоли в символах, или -1, если не удалось его получить |


#### getCurrentPath()
Получает имя каталога, в котором выполняется программа
| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `string` | Строку – путь до текущего каталога |


#### getFIleExtention(name)
Получает расширение переданного имени файла
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `name` | `string` | **Required**. Имя файла с расширением |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `string` | Расширение, или "-1", если имя не содержит расширения |


#### isLetter(c)
Проверяется, является ли переданный символ буквенно-кириллическим
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `с` | `wchar_t` | **Required**. Символ в кодировке ANSI |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `bool` | true - если является false - если не является |


#### log(s, [mode], [br])
Выводит красиво оформленную строку в консоль
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `s` | `wstring` | **Required**. Строка которую необходимо вывести |
| `mode` | `ConsoleFormats` | Тип префикса перед ней |
| `br` | `bool` | Следует ли переносить строку перед выводом записи |


#### printHeader()
Выводит в консоль заголовок программы с вариантом, группой и фио

#### getFileData()
Запрашивает у пользователя путь до файла исходных данных

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `FileData` | Структуру, хранящую в себе путь до файла, его имя и расширение |


#### readFromFile(InputFile)
Считывает данные из файлового потока ввода в строку
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `InputFile` | `wifstream&` | **Required**. Поток ввода |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `wstring` | Строку с содержимым файла |


#### writeIntoResultFIle(A, OutputFile)
Записывает отсортированный массив в файл результата
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `A` | `vector<wstring> ` | **Required**. Отсортированный массив (вектор) |
| `OutputFile` | `wofstream&` | **Required**. Поток файла результата |

#### writeIntoStatisticFIle(txt, n, t, a, OutputFile)
Записывает данные в файл анализа/статистики, и рассчитывает
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `txt` | `wstring` | **Required**. Текст из исходного файла |
| `n` | `int` | **Required**. Количество слов в массиве |
| `t` | `double` | **Required**. Время сортировки |
| `a` | `vector<wstring>` | **Required**. Отсортированный массив (вектор) |
| `OutputFile` | `wofstream&` | **Required**. Поток файла статистики |


#### split(str)
Разбивает кириллическую строку на слова
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `str` | `wstring ` | **Required**. Исходная строка |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `vector<wstring>` | **Required**. Массив (вектор) слов |


#### shell(A)
Сортирует массив (вектор) методом Шелла 
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `A` | `vector<wstring>& ` | **Required**. Указатель на сортируемый массив |


#### benchmark(vector<wstring>& a, void (*f)(vector<wstring>&))
Осуществляет замер времени выполнения функции
| Параметр | Тип     | Описание                |
| :-------- | :------- | :------------------------- |
| `a` | `vector<wstring>& ` | **Required**. Указатель на сортируемый массив (вектор) |
| `f` | `void (*f)(vector<wstring>&) ` | **Required**. Указатель на функцию обратного вызова (сортировщик) |

| Возвращает    | Описание                |
| :-------- | :------------------------- |
| `double` | массив (вектор) слов |

### main

```c++
/*****************************************************************
\file
\brief Входной файл проекта
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
```

