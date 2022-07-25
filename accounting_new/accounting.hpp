#pragma once
#include "./users/users.cpp"
#include <vector>
#include <string>
using namespace std;

class AccountingGoods : public Database
{
    string note_path; // путь к файлу с базой данных
    vector<Database> notes;
    Accounts curr_user;

public:
    AccountingGoods() // конструктор по умолчнанию
    {
        note_path = "/Users/macvejpazh/Documents/proga/accounting_new/note.txt";
    }
    AccountingGoods(string note_path, vector<Database> &notes, Accounts &curr_user)
        : note_path(note_path), notes(notes), curr_user(curr_user){};
    // коструктор со значениями

    ////
    void Authorisation();                                               // авторизация
    int FindLogin(vector<Accounts> &accounts, string login, uint role); // поиск логина
    void Menu();                                                        // меню - основная функция
    void FillVector();
    void FillVector(vector<Accounts> &users); // заполнение контейнеров
    void ViewNotes();                         // вывод базы данных
    void AddNote();                           // добавление записи
    void DeleteNote();                        //удаление записи
    void EditNote();                          // редактирование записи
    void Search();                            // поиск
    void FilterSearch();                      // поиск с фильтрацией
    void Sort();                              // сортировка
    // функции администратора
    void ManageAccounts();                        // управление аккаунтами
    void ViewAccounts(vector<Accounts> &users);   // вывод данных аккаунтов
    void AddAccounts(vector<Accounts> &users);    // добавление аккаунта
    void EditAccounts(vector<Accounts> &users);   // редактирование аккаунта
    void DeleteAccounts(vector<Accounts> &users); // удаление аккаунта
    //
    void FileHandling(); // работа с файлами
    void OpenFile();     // открытие файла
    void CreateFile();   // создание файла
    void DeleteFile();   // удаление файла
    void OutputNotes();  // запись данных в файл
    //дополнительные функции
    void ViewNote(vector<Database>::iterator it, uint id);     // вывод одной записи
    void OutputAccounts(vector<Accounts> &users, string path); // запись данных аккаунта в файл
};
