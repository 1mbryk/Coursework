#include "users.hpp"
using namespace std;

bool RoleControl(uint role) // проверка правильности ввода роли
{
    return role < 2;
}

void Accounts::SetLogin(string login)
{
    this->login = login;
}
void Accounts::SetPassword(string password)
{
    this->password = password;
}
void Accounts::SetRole(uint role)
{
    this->role = data_control(role, RoleControl, "РОЛЬ");
}
void Accounts::SetPath(string path)
{
    this->accounts_path = path;
}

string Accounts::GetLogin() const
{
    return login;
}
string Accounts::GetPassword() const
{
    return password;
}
uint Accounts::GetRole() const
{
    return role;
}
string Accounts::GetPath() const
{
    return this->accounts_path;
}

void Accounts::EditPath()
{
    bool confirm = false;
    cout << "ИСПОЛЬЗОВАТЬ ПУТЬ ПО УМОЛЧАНИЮ? (" << accounts_path << ")\n"
         << "1. ДА.\n"
         << "0. НЕТ.\n";
    cin >> confirm;
    if (!confirm)
    {
        cout << "ВВЕДИТЕ ПОЛНЫЙ ПУТЬ К ФАЙЛУ:\n";
        cin >> accounts_path;
    }
}

bool Accounts::operator==(Accounts &other) // перегрузка оператора сравнивания
{
    return (this->login == other.login && this->password == other.password && this->role == other.role);
}
