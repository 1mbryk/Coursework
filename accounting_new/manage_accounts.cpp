#pragma once
#include "accounting.cpp"
#include "database.cpp"
using namespace std;

void AccountingGoods::ManageAccounts() // управление аккаутами
{

    enum Menu
    {
        BACK,
        VIEW,
        ADD,
        EDIT,
        DELETE,
    };
    int choice = 0;
    vector<Accounts> users;

    FillVector(users);
    while (true)
    {
        cout << setw(52) << internal << "УПРАВЛЕНИЕ АККАУНТАМИ" << endl;
        cout << "1. ПРОСМОТР ВСЕХ УЧËТНЫХ ЗАПИСЕЙ.\n"
             << "2. ДОБАВЛЕНИЕ УЧËТНЫХ ЗАПИСЕЙ.\n"
             << "3. РЕДАКТИРОВАНИЕ УЧËТНЫХ ЗАПИСЕЙ.\n"
             << "4. УДАЛЕНИЕ УЧËТНЫХ ЗАПИСЕЙ.\n"
             << "0. НАЗАД.\n";
        cin >> choice;
        switch (choice)
        {
        case VIEW:
            cout << setw(48) << internal << "ПРОСМОТР АККАУНТОВ" << endl;
            ViewAccounts(users);
            break;
        case ADD:
            AddAccounts(users);
            break;
        case EDIT:
            EditAccounts(users);
            break;
        case DELETE:
            DeleteAccounts(users);
            break;
        case BACK:
            return;
        default:
            break;
        }
    }
}

void AccountingGoods::ViewAccounts(vector<Accounts> &users) // просмотр аккаунтов
{
    vector<Accounts>::iterator it = users.begin();
    cout << setw(2) << "#" << '|'
         << setw(14) << left << "ЛОГИН" << right << '|'
         << setw(14) << left << "ПАРОЛЬ" << right << '|'
         << setw(9) << left << "РОЛЬ" << right << '|' << endl;
    int i = 1;
    for (; it != users.end(); ++it, ++i)
    {
        cout << setw(2) << i << '|'
             << setw(9) << left << it->GetLogin() << right << '|'
             << setw(8) << left << it->GetPassword() << right << '|'
             << setw(5) << left << it->GetRole() << right << '|' << endl;
    }
}

void AccountingGoods::AddAccounts(vector<Accounts> &users) // добавление аккаунта
{
    cout << setw(50) << internal << "ДОБАВЛЕНИЕ АККАУНТА" << endl;
    Accounts new_user;
    uint role;
    string login;
    string password;
    cout << "ВВЕДИТЕ РОЛЬ: ";
    cin >> role;
    role = data_control(role, RoleControl, "РОЛЬ"); // функция проверки правильности введённых данных
    cout << "ВВЕДИТЕ ЛОГИН: ";
    cin >> login;
    while (FindLogin(users, login, role) != -1)
    {
        cout << "УЧËТНАЯ ЗАПИСЬ С ТАКИМ ЛОГИНОМ УЖЕ СУЩЕСТВУЕТ.\n"
             << "ВВЕДИТЕ ЛОГИН: ";
        cin >> login;
    }
    cout << "ВВЕДИТЕ ПАРОЛЬ: ";
    cin >> password;
    new_user.SetRole(role);
    new_user.SetLogin(login);
    new_user.SetPassword(password);
    users.push_back(new_user);
    OutputAccounts(users, new_user.GetPath());
    cout << "УЧËТНАЯ ЗАПИСЬ ДОБАВЛЕНА.\n";
}

void AccountingGoods::EditAccounts(vector<Accounts> &users) // редактировать аккаунт
{
    cout << setw(65) << internal << "РЕДАКТИРОВАНИЕ УЧËТНЫХ ЗАПИСЕЙ" << endl;
    ViewAccounts(users);
    uint index = 0;
    cout << "ВВЕДИТЕ ПРОЯДКОВЫЙ НОМЕР ЗАПИСИ: ";
    cin >> index;
    index--;
    while (index > users.size())
    {
        cout << "НЕВЕРНЫЙ ПОРЯДКОВЫЙ НОМЕР.\n"
             << "ВВЕДИТЕ ПРОЯДКОВЫЙ НОМЕР ЗАПИСИ: ";
        cin >> index;
    }
    string login;
    string password;
    cout << "ВВЕДИТЕ НОВЫЙ ЛОГИН: ";
    cin >> login;
    cout << "ВВЕДИТЕ НОВЫЙ ПАРОЛЬ: ";
    cin >> password;
    users.at(index).SetLogin(login);
    users.at(index).SetPassword(password);
    OutputAccounts(users, users[index].GetPath());
    cout << "УЧËТНАЯ ЗАПИСЬ ОТРЕДАКТИРОВАНА.\n";
}

void AccountingGoods::DeleteAccounts(vector<Accounts> &users) // удаление аккаунта
{
    cout << setw(56) << internal << "УДАЛЕНИЕ УЧËТНЫХ ЗАПИСЕЙ" << endl;
    ViewAccounts(users);
    uint index = 0;
    cout << "ВВЕДИТЕ ПРОЯДКОВЫЙ НОМЕР ЗАПИСИ: ";
    cin >> index;
    index--;
    while (index > users.size())
    {
        cout << "НЕВЕРНЫЙ ПОРЯДКОВЫЙ НОМЕР.\n"
             << "ВВЕДИТЕ ПРОЯДКОВЫЙ НОМЕР ЗАПИСИ: ";
        cin >> index;
    }
    bool confirm = false;
    cout << "ВЫ УВЕРЕНЫ?\n"
         << "0. НЕТ.\n"
         << "1. ДА.\n";
    cin >> confirm;
    if (!confirm)
        return;
    users.erase(users.begin() + index);
    OutputAccounts(users, users.at(0).GetPath());
    cout << "ЗАПИСЬ УДАЛЕНА.\n";
}

void AccountingGoods::OutputAccounts(vector<Accounts> &users, string path) // функция вывода
                                                                           //данных аккаунта в файл по пути accounts_path
{
    ofstream fout(path, ios::trunc);
    vector<Accounts>::iterator it = users.begin();
    for (; it < users.end(); ++it)
    {
        if (fout.tellp() != fout.beg)
            fout << endl;
        fout << it->GetLogin() << ' '
             << it->GetPassword() << ' '
             << it->GetRole();
    }
    fout.close();
}
