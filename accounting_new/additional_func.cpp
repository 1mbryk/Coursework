#pragma once
#include "accounting.hpp"
#include "sort.hpp"

int AccountingGoods::FindLogin(vector<Accounts> &accounts, string login, uint role)
{ // функия поиска логина
    int index = -1;
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].GetLogin() == login && accounts[i].GetRole() == role)
        {
            index = i;
            break;
        }
    }
    return index;
}

void AccountingGoods::FillVector(vector<Accounts> &users)
{ // функия заполнения контейнера с данными аккаунтов
    Accounts temp;
    ifstream fin(temp.GetPath());
    if (!fin.is_open())
    {
        string err = "ФАЙЛ НЕ ОТКРЫТ!";
        throw err;
    }
    while (fin)
    {
        if (fin.eof())
            break;
        temp.SetLogin(InputData<string>(fin));
        temp.SetPassword(InputData<string>(fin));
        temp.SetRole(InputData<uint>(fin));
        users.push_back(temp);
    }
}

void AccountingGoods::FillVector()
{ // функция заролнения контейнера с базой данных
    ifstream fin(note_path);
    Database temp;
    string name;
    uint amount;
    float price;
    string date;
    while (fin)
    {
        if (fin.eof())
            break;
        temp.SetAllData(InputData(fin), InputData<uint>(fin),
                        InputData<float>(fin), InputData<string>(fin));
        notes.push_back(temp);
        fin.seekg(1 + fin.tellg());
    }
    fin.close();
}

void ViewHeader()
{ // функция вывода шапки таблицы
    cout << setw(2) << left << "#" << '|'
         << setw(40) << left << "НАИМЕНОВАНИЕ" << right << '|'
         << setw(12) << left << "КОЛ-ВО" << right << '|'
         << setw(10) << left << "ЦЕНА" << right << '|'
         << setw(15) << left << "ДАТА" << right << '|' << endl
         << setw(60) << setfill('-') << "|\n"
         << setfill(' ');
}

void AccountingGoods::ViewNote(vector<Database>::iterator it, uint id)
{ // функция вывода одного элемента
    cout << setw(2) << left << id << right << '|'
         << setw(28) << left << it->GetName() << right << '|'
         << setw(7) << left << it->GetAmount() << right << '|'
         << setw(6) << left << fixed << setprecision(2) << it->GetPrice() << right << '|'
         << setw(11) << left << it->GetDate() << right << '|' << endl;
}
