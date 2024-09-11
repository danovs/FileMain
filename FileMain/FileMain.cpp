#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <string>

using namespace std;

typedef void (*ReplaceDigitsWithWordFunction)(const char*, const char*, int);

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string inputFilePath, outputFilePath;
    int replaceCount;

    cout << "Введите путь к входному файлу: ";
    getline(cin, inputFilePath);

    cout << "Введите путь к выходному файлу: ";
    getline(cin, outputFilePath);

    cout << "Введите количество замен: ";
    cin >> replaceCount;

    // Загружаем DLL
    HMODULE hDll = LoadLibrary(L"C:\\DLL\\FileProcessor.dll");
    if (!hDll) {
        cerr << "Не удалось загрузить DLL." << endl;
        return 1;
    }

    
    ReplaceDigitsWithWordFunction replaceDigitsWithWord = (ReplaceDigitsWithWordFunction)GetProcAddress(hDll, "ReplaceDigitsWithWord");
    if (!replaceDigitsWithWord) {
        cerr << "Не удалось найти функцию ReplaceDigitsWithWord в библиотеке." << endl;
        FreeLibrary(hDll);
        return 1;
    }

    try {
        replaceDigitsWithWord(inputFilePath.c_str(), outputFilePath.c_str(), replaceCount);
        cout << "Обработка файла завершена." << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        FreeLibrary(hDll);
        return 1;
    }

    FreeLibrary(hDll);
    return 0;
}