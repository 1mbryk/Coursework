#pragma once
#include "accounting.cpp"
#include <fstream>
using namespace std;

void char_copy(char *copy_to, string copy_from);
void AccountingGoods::FileHandling()
{
    enum Menu
    {
        BACK,
        OPEN,
        CREATE,
        DELETE,
    };
    int choice = 0;
    while (true)
    {
        cout << setw(43) << internal << "РАБОТА С ФАЙЛАМИ" << endl;
        cout << "1. ОТКРЫТЬ ФАЙЛ.\n"
             << "2. СОЗДАТЬ ФАЙЛ.\n"
             << "3. УДАЛИТЬ ФАЙЛ.\n"
             << "0. НАЗАД.\n";
        cin >> choice;
        switch (choice)
        {
        case OPEN:
            OpenFile();
            break;
        case CREATE:
            CreateFile();
            break;
        case DELETE:
            DeleteFile();
            break;
        case BACK:
            return;
        default:
            break;
        }
    }
}

void AccountingGoods::CreateFile() // создание файла
{
    string path;
    cout << setw(41) << internal << "СОЗДАНИЕ ФАЙЛА" << endl;
    cout << "ВВЕДИТЕ ПОЛНЫЙ ПУТЬ К ФАЙЛУ: ";
    cin >> path;
    ofstream fout;
    fout.open(path);
    if (!fout.is_open())
        cout << "ФАЙЛ НЕ СОЗДАН.\n";
    else
        cout << "ФАЙЛ СОЗДАН.\n";
    fout.close();
}

void AccountingGoods::OpenFile() // открытие файла
{
    cout << setw(41) << internal << "ОТКРЫТИЕ ФАЙЛА" << endl;
    string path;
    cout << "ВВЕДИТЕ ПОЛНЫЙ ПУТЬ К ФАЙЛУ: ";
    cin >> path;
    ifstream fin(path);
    if (!fin.is_open())
    {
        cout << "ФАЙЛ НЕ ОТКРЫТ!" << endl;
        return;
    }
    string data;
    fin.seekg(ios::end);
    if (!fin.tellg())
    {
        cout << "ФАЙЛ ПУСТ." << endl;
        return;
    }
    fin.seekg(ios::beg);
    while (fin)
    {
        if (fin.eof())
        {
            break;
        }
        getline(fin, data);
        cout << data << endl;
    }
    cout << endl;
}

void AccountingGoods::DeleteFile() // удаление файла
{
    cout << setw(41) << internal << "УДАЛЕНИЕ ФАЙЛА" << endl;
    string path;
    cout << "ВВЕДИТЕ ПОЛНЫЙ ПУТЬ К ФАЙЛУ: ";
    cin >> path;
    bool confirm = false;
    cout << "ВЫ УВЕРЕНЫ?\n"
         << "1. ДА\n"
         << "0. НЕТ\n";
    cin >> confirm;
    if (!confirm)
        return;
    char *ch_path = new char[path.length() + 1];
    char_copy(ch_path, path);

    if (remove(ch_path))
        cout << "ФАЙЛ НЕ УДАЛËН\n";
    else
        cout << "ФАЙЛ УДАЛËН.\n";
}

void char_copy(char *copy_to, string copy_from) // преведение char* к string
{
    for (int i = 0; i < copy_from.length(); i++)
    {
        copy_to[i] = copy_from[i];
    }
}