#include <iostream>

using namespace std;

class Date // класс даты
{
    uint day;                                                                          // день поступления
    uint month;                                                                        // месяц поступления
    uint year;                                                                         // год поступления
    Date(int day, uint month, uint year) : day(day), month(month), year(year){};       // конструктор по значению
    Date() : day(0), month(0), year(0){};                                              // коструктор по умолчанию
    Date(const Date &other) : day(other.day), month(other.month), year(other.month){}; //конструктор копирования

    friend class Database;
    void init(int day, uint month, uint year)
    {
        Date(day, month, year);
    }
    Date &operator=(const Date &other);
};

class Database // класс базы данных
{
    string name; // наименование товара
    uint amount; // количество товара
    float price; // цена товара
    Date date;   // дата поступления товара

public:
    Database() : name("\0"), amount(0), price(0){}; // конструктор по умлочанию
    Database(uint id, string name, uint amount, float price, uint day, uint month, uint year)
    { // конструктор со значениями
        this->name = name;
        this->amount = amount;
        this->price = price;
        this->date.init(day, month, year);
    }
    Database(const Database &other) // конструктор копирования
    {
        this->name = other.name;
        this->amount = other.amount;
        this->price = other.price;
        this->date = other.date;
    }
    string GetName() const;
    uint GetAmount() const;
    float GetPrice() const;
    string GetDate() const;

    void SetName(string name);
    void SetAmount(uint amount);
    void SetPrice(float price);
    void SetDate(uint day, uint month, uint year);
    void SetDate(string date);

    void SetAllData(string name, uint amount, float price, uint day, uint month, uint year);
    void SetAllData(string name, uint amount, float price, string date);
    bool operator>(const Database &other) const; // перегрузка оператора больше
    bool operator<(const Database &other) const; // перегрузка оператора меньше
    int DateCompare(string date);                // функция сравнивания даты
};
