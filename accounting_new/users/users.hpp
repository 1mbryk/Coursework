#pragma once
#include <string>
#include <iomanip>
#include "../database.cpp"
#include <fstream>
using namespace std;
class Accounts // класс хранящий в себе данные аккаунтов
{
    string login;
    string password;
    uint role;
    string accounts_path; // путь к файлу с данными

public:
    Accounts() : login("\n"), password("\n"), role(-1), accounts_path("/Users/macvejpazh/Documents/proga/accounting_new/users/accounts.txt"){};
    Accounts(string login, string password, uint role, string accounts_path)
        : login(login), password(password), role(role), accounts_path(accounts_path){};
    Accounts(const Accounts &other)
    {
        login = other.login;
        password = other.password;
        role = other.role;
        accounts_path = other.accounts_path;
    }
    void SetLogin(string login);
    void SetPassword(string password);
    void SetRole(uint role);
    void SetPath(string path);

    string GetLogin() const;
    string GetPassword() const;
    uint GetRole() const;
    string GetPath() const;
    void EditPath(); // 1 - admin, 0 - user

    bool operator==(Accounts &other);
    ~Accounts()
    {
        login.clear();
        password.clear();
        role = -1;
        accounts_path.clear();
    }
};
