#pragma once
#include "accounting.hpp"      // заголовочный файл с описанием класса
#include "additional_func.cpp" // дополнительные функции, которые используются в методах
#include "manage_accounts.cpp" // реализация методоа "управление аккаунтами"
#include "file_handling.cpp"   // рализация методов "работа с файлами"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void AccountingGoods::Authorisation() // функция авторизации
{

    vector<Accounts> all_accounts; // контейнер класса с данными аккаунтов

    ifstream fin(curr_user.GetPath());
    FillVector(all_accounts);
    int index = 0;
    if (all_accounts.empty())
    {
        cout << "ФАЙЛ ПУСТ." << endl;
        AddAccounts(all_accounts);
    }

    cout << setw(38) << internal << "АВТОРИЗАЦИЯ" << endl;
    cout << "ВЫБЕРЕТЕ РОЛЬ:\n"
         << "1. АДМИНИСТРАТОР.\n"
         << "0. ПОЛЬЗОВАТЕЛЬ.\n";
    curr_user.SetRole(InputData<uint>());
    do
    {
        if (index < 0)
            cout << "ЛОГИН \"" << curr_user.GetLogin() << "\" НЕ НАЙДЕН.\n";
        cout << "ВВЕДИТЕ ЛОГИН: ";
        curr_user.SetLogin(InputData<string>());
        index = FindLogin(all_accounts, curr_user.GetLogin(), curr_user.GetRole());
    } while (index < 0);
    cout << "ВВЕДИТЕ ПАРОЛЬ: ";
    curr_user.SetPassword(InputData<string>());
    while (all_accounts[index].GetPassword() != curr_user.GetPassword())
    {
        cout << "НЕВЕРНЫЙ ПАРОЛЬ.\n"
             << "ВВЕДИТЕ ПАРОЛЬ: ";
        curr_user.SetPassword(InputData<string>());
    }
}

void AccountingGoods::Menu() // основная функция
{
    Authorisation();
    enum MENU
    {
        EXIT,
        VIEW_NOTE,
        ADD_NOTE,
        DELETE_NOTE,
        EDIT_NOTE,
        SEARCH,
        FILTER_SEARCH,
        SORT,
        MANAGE_ACC,
        FILE_HANDLING,

    };
    FillVector(); // функция заполнения контейнера с базой данных
    int choice = -1;
    while (true)
    {
        cout << setw(27) << internal << "МЕНЮ" << endl;
        cout << "1. ПОКАЗАТЬ ЗАПИСЬ. \n"
             << "2. ДОБАВИТЬ ЗАПИСЬ. \n"
             << "3. УДАЛИТЬ ЗАПИСЬ.\n"
             << "4. РЕДАКТИРОВАТЬ ЗАПИСЬ\n"
             << "5. ПОИСК.\n"
             << "6. ПОИСК С ФИЛЬТРАЦИЕЙ.\n"
             << "7. СОРТИРОВКА.\n";
        if (curr_user.GetRole())
        {
            cout << "8. УПРАВЛЕНИЕ АККАУНТАМИ.\n"
                 << "9. РАБОТА С ФАЙЛАМИ ДАННЫХ.\n";
        }
        cout << "0. ВЫХОД.\n";
        cin >> choice;
        switch (choice)
        {
        case EXIT:
            cout << "ПРОГРАММА ЗАВЕРШАЕТСЯ.";
            return;
        case VIEW_NOTE:
            ViewNotes();
            break;
        case ADD_NOTE:
            AddNote();
            break;
        case DELETE_NOTE:
            DeleteNote();
            break;
        case EDIT_NOTE:
            EditNote();
            break;
        case SEARCH:
            Search();
            break;
        case FILTER_SEARCH:
            FilterSearch();
            break;
        case SORT:
            Sort();
            break;
        default:
            break;
        }
        if (curr_user.GetRole()) // функции администратора
        {
            switch (choice)
            {
            case MANAGE_ACC:
                ManageAccounts();
                break;
            case FILE_HANDLING:
                FileHandling();
                break;
            default:
                break;
            }
        }
    }
}

void AccountingGoods::ViewNotes() // просмотр базы данных
{
    vector<Database>::iterator it = notes.begin();
    ViewHeader();
    for (int i = 1; it < notes.end(); ++it, ++i)
    {

        cout << setw(2) << left << i << right << '|'
             << setw(28) << left << it->GetName() << right << '|'
             << setw(7) << left << it->GetAmount() << right << '|'
             << setw(6) << left << fixed << setprecision(2) << it->GetPrice() << right << '|'
             << setw(11) << left << it->GetDate() << right << '|' << endl;
    }
}

void AccountingGoods::AddNote() // добавление записи
{
    cout << setw(46) << internal << "ДОБАВЛЕНИЕ ЗАПИСИ" << endl;
    Database new_note;
    string name;
    uint amount;
    float price;
    string date;
    cout << "ВВЕДИТЕ НАИМЕНОВАНИЕ: ";
    cin.ignore(4096, '\n');
    getline(cin, name);
    cout << "ВВЕДИТЕ КОЛИЧЕСТВО: ";
    cin >> amount;
    cout << "ВВЕДИТЕ ЦЕНУ: ";
    cin >> price;
    cout << "ВВЕДИТЕ ДАТУ (ДД.ММ.ГГГГ): ";
    cin >> date;
    new_note.SetAllData(name, amount, price, date); // заполнение элемента класса
    notes.push_back(new_note);
}

void AccountingGoods::DeleteNote() // удаление записи
{
    cout << setw(43) << internal << "УДАЛЕНИЕ ЗАПИСИ" << endl;
    int id = -1;
    bool confirm = false;
    vector<Database>::iterator it = notes.begin();
    ViewNotes();
    cout << "ВВЕДИТЕ НОМЕР ЗАПИСИ: ";
    cin >> id;
    --id;
    if (id < 0 || id >= notes.size())
    {
        string err = "ВВЕДËН НЕПРАВИЛЬНЫЙ НОМЕР.\n";
        throw err;
    }
    it += id;
    cout << "?\n"
         << "0. НЕТ.\n"
         << "1. ДА.\n";
    cin >> confirm;
    if (!confirm) // подтверждение удаления
        return;
    notes.erase(it);
    cout << "ЗАПИСЬ УДАЛЕНА.\n";
    OutputNotes(); // запись данных в файл
}

void AccountingGoods::EditNote() // редактирование записи
{
    cout << setw(51) << internal << "РЕДАКТИРОВАНИЕ ЗАПИСИ" << endl;
    ViewNotes();
    int id = -1;
    cout << "ВВЕДИТЕ ПОРЯДКОВЫЙ НОМЕР ТОВАРА: ";
    cin >> id;
    --id;
    if (id < 0 || id >= notes.size())
    {
        string err = "ВВЕДËН НЕПРАВИЛЬНЫЙ НОМЕР.\n";
        throw err; // обработка исключений
    }
    enum EDIT
    {
        BACK,
        NAME,
        AMOUNT,
        PRICE,
        DATE,
        ALL
    };
    int choice = 0;
    cout << "ВЫБЕРИТЕ ДАННЫЕ ДЛЯ РЕДАКТИРОВАНИЯ:\n"
         << "1. НАИМЕНОВАНИЕ.\n"
         << "2. КОЛИЧЕСТВО.\n"
         << "3. ЦЕНА.\n"
         << "4. ДАТА.\n"
         << "5. ВСЕ.\n"
         << "0. НАЗАД.\n";
    cin >> choice;
    string name;
    uint amount = 0;
    float price = 0;
    string date;
    switch (choice)
    {
    case NAME:
        cout << "ВВЕДИТЕ НАИМЕНОВАНИЕ ТОВАРА: ";
        cin.ignore(4096, '\n');
        getline(cin, name);
        notes[id].SetName(name);
        break;
    case AMOUNT:
        cout << "ВВЕДИТЕ КОЛИЧЕСТВО: ";
        cin >> amount;
        notes[id].SetAmount(amount);
        break;
    case PRICE:
        cout << "ВВЕДИТЕ ЦЕНУ: ";
        cin >> price;
        notes[id].SetPrice(price);
        break;
    case DATE:
        cout << "ВВЕДИТЕ ДАТУ ПОСТУПЛЕНИЯ: ";
        cin >> date;
        notes[id].SetDate(date);
        break;
    case ALL:
        cout << "ВВЕДИТЕ НАИМЕНОВАНИЕ ТОВАРА: ";
        cin.ignore(4096, '\n');
        getline(cin, name);
        cout << "ВВЕДИТЕ КОЛИЧЕСТВО: ";
        cin >> amount;
        cout << "ВВЕДИТЕ ЦЕНУ: ";
        cin >> price;
        cout << "ВВЕДИТЕ ДАТУ ПОСТУПЛЕНИЯ: ";
        cin >> date;
        notes[id].SetAllData(name, amount, price, date);
        break;

    case BACK:
        return;
    default:
        break;
    }
    cout << "ЗАПИСЬ ДОБАВЛЕНА.\n";
    OutputNotes();
}

void AccountingGoods::Search() //поиск
{
    cout << setw(28) << internal << "ПОИСК" << endl;
    enum SEARCH
    {
        BACK,
        NAME,
        AMOUNT,
        PRICE,
        DATE,
    };
    int choice = 0;
    cout << "ВЫБЕРИТЕ ТИП ПОИСКА:\n"
         << "1. ПО НАЗВАНИЮ.\n"
         << "2. ПО КОЛИЧЕСТВУ.\n"
         << "3. ПО ЦЕНЕ.\n"
         << "4. ПО ДАТЕ.\n"
         << "0. НАЗАД.\n";
    cin >> choice;
    bool result_search = false;
    string name; // данные по которым производится поиск
    uint amount;
    float price;
    string date;
    vector<Database>::iterator it = notes.begin();
    switch (choice)
    {
    case NAME:
        cout << "ВВЕДИТЕ НАЗВАНИЕ: ";
        cin.ignore(4096, '\n');
        getline(cin, name);
        for (; it < notes.end(); ++it)
        {
            if (it->GetName() == name)
            {
                result_search = true;
                break;
            }
        }
        break;
    case AMOUNT:
        cout << "ВВЕДИТЕ КОЛИЧЕСТВО: ";
        cin >> amount;
        for (; it < notes.end(); ++it)
        {
            if (it->GetAmount() == amount)
            {
                result_search = true;
                break;
            }
        }
        break;
    case PRICE:
        cout << "ВВЕДИТЕ ЦЕНУ: ";
        cin >> price;
        for (; it < notes.end(); ++it)
        {
            if (it->GetPrice() == price)
            {
                result_search = true;
                break;
            }
        }
        break;
    case DATE:
        cout << "ВВЕДИТЕ ДАТУ (ДД.ММ.ГГГГ): ";
        cin >> date;
        for (; it < notes.end(); ++it)
        {
            if (it->GetDate() == date)
            {
                result_search = true;
                break;
            }
        }
        break;
    case BACK:
        return;
    default:
        break;
    }
    if (result_search)
    {
        cout << "ЗАПРАШИВАЕМАЯ ЗАПИСЬ:\n";
        ViewHeader();
        ViewNote(it, 1);
    }
    else
        cout << "ЗАПИСИ С ТАКИМ ПАРАМЕТРОМ НЕ НАЙДЕНО.\n";
}

void AccountingGoods::FilterSearch() // поиск с фильтрацией
{
    cout << setw(47) << internal << "ПОИСК С ФИЛЬТРАЦИЕЙ" << endl;
    float price;
    string date;
    cout << "ВВЕДИТЕ ЦЕНУ: ";
    cin >> price;
    cout << "ВВЕДИТЕ ДАТУ (ДД.ММ.ГГГ): ";
    cin >> date;
    vector<Database>::iterator it = notes.begin();
    bool search_result = false;
    for (int i = 0; it < notes.end(); ++it)
    {
        if (it->GetPrice() >= price && it->DateCompare(date) == 1)
        {
            search_result = true;
            if (!(i++))
                ViewHeader(); // вывод шапки таблицы
            ViewNote(it, i);
        }
    }
    if (!search_result)
        cout << "ЗАПИСЬ НЕ НАЙДЕНА.\n";
}

void AccountingGoods::Sort() // сортировка записи
{
    int choice = 0;
    enum SORT
    {
        BACK,
        NAME_DEC,
        NAME_INC,
        AMOUNT_INC,
        AMOUNT_DEC,
        PRICE_INC,
        PRICE_DEC,
    };
    while (true)
    {
        cout << setw(36) << internal << "СОРТИРОВКА" << endl;
        cout << "ВЫБЕРИТЕ ПО КАКОМУ ПОЛЮ СОРТИРОВАТЬ:\n"
             << "1. ПО НАЗВАНИЮ. (В АЛФАВИТНОМ ПОРЯДКЕ)\n"
             << "2. ПО НАЗВАНИЮ. (В НЕ АЛФАВИТНОМ ПОРЯДКЕ)\n"
             << "3. ПО КОЛИЧЕСТВУ. (ПО ВОЗРАСТАНИЮ)\n"
             << "4. ПО КОЛИЧЕСТВУ. (ПО УБЫВАНИЮ)\n"
             << "5. ПО ЦЕНЕ. (ПО В0ЗРАСТАНИЮ)\n"
             << "6. ПО ЦЕНЕ. (ПО УБЫВАНИЮ)\n"
             << "0. НАЗАД.\n";
        cin >> choice;
        switch (choice)
        {
        case BACK:
            return;
        case NAME_DEC:
            QuickSort(notes, NameCompareDecrease, 0, notes.size() - 1);
            break;
        case NAME_INC:
            QuickSort(notes, NameCompareIncrease, 0, notes.size() - 1);
            break;
        case AMOUNT_INC:
            QuickSort(notes, AmountCompareIncrease, 0, notes.size() - 1);
            break;
        case AMOUNT_DEC:
            QuickSort(notes, AmountCompareDecrease, 0, notes.size() - 1);
            break;
        case PRICE_INC:
            QuickSort(notes, PriceCompareIncrease, 0, notes.size() - 1);
            break;
        case PRICE_DEC:
            QuickSort(notes, PriceCompareDecrease, 0, notes.size() - 1);
            break;

        default:
            break;
        }
        ViewNotes();
        OutputNotes();
    }
}

void AccountingGoods::OutputNotes() // запись данных в файл
{
    ofstream fout(note_path);
    vector<Database>::iterator it = notes.begin();
    for (; it < notes.end(); ++it)
    {
        if (fout.tellp() != fout.beg)
            fout << endl;
        fout << it->GetName() << endl
             << it->GetAmount() << ' '
             << it->GetPrice() << ' '
             << it->GetDate();
    }
    fout.close();
}