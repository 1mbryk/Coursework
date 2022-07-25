#pragma once
#include "database.hpp"
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

Date &Date::operator=(const Date &other) // перегрузка оператора присвоения копированием
{
    if (this == &other)
        return *this;
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
    return *this;
}

template <typename type>
type data_control(type data, bool (*control)(type), const char *name)
{ // функция проверки правильности введённых данных

    while (cin.fail() || !control(data)) // функция "шаблон" для проверки данных
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(4096, '\n');
            cin.sync();
        }
        cout << "НЕВЕРНЫЕ ДАННЫЕ\n"
             << "ПОВТОРНО ВВЕДИТЕ ДАННЫЕ(" << name << "):";
        cin >> data;
    }

    return data;
}

string Database::GetName() const
{
    return name;
}
uint Database::GetAmount() const
{
    return amount;
}
float Database::GetPrice() const
{
    return price;
}
string Database::GetDate() const
{
    return to_string(date.day) + '.' + to_string(date.month) + '.' + to_string(date.year);
}

void Database::SetName(string name)
{
    this->name = name;
}

void Database::SetAmount(uint amount)
{
    this->amount = amount;
}

bool price_control(float price)
{
    return price > 0;
}
void Database::SetPrice(float price)
{
    price = data_control<float>(price, price_control, "ЦЕНА");
    this->price = price;
}

bool day_control31(uint day) // функции проверки дней в зависимости от месяцев
{
    return day > 0 && day < 32;
}
bool day_control30(uint day)
{
    return day > 0 && day < 31;
}
bool day_control28(uint day)
{
    return day > 0 && day < 29;
}

bool mounth_control(uint month)
{
    return month > 0 && month < 13;
}
bool year_control(uint year)
{
    return year > 0;
}

void Database::SetDate(uint day, uint month, uint year)
{

    month = data_control(month, mounth_control, "МЕСЯЦ"); // поверка правильности введённых данных
    year = data_control(year, year_control, "ГОД");
    if ((month % 2 && month < 8) || !(month % 2) && month > 7)
    {
        day = data_control(day, day_control31, "ДЕНЬ");
    }
    else if (month == 2)
    {
        day = data_control(day, day_control28, "ДЕНЬ");
    }
    else
    {
        day = data_control(day, day_control30, "ДЕНЬ");
    }
    this->date.day = day;
    this->date.month = month;
    this->date.year = year;
}

uint devide(string &buf);
int to_int(string str);
void Database::SetDate(string date)
{
    uint day = devide(date);
    uint month = devide(date);
    uint year = devide(date);
    SetDate(day, month, year);
}

void Database::SetAllData(string name, uint amount,
                          float price, uint day, uint month, uint year)
{
    this->SetName(name);
    this->SetAmount(amount);
    this->SetPrice(price);
    this->SetDate(day, month, year);
}
void Database::SetAllData(string name, uint amount,
                          float price, string date)
{
    this->SetName(name);
    this->SetAmount(amount);
    this->SetPrice(price);
    this->SetDate(date);
}

bool Database::operator<(const Database &other) const // перегрузка оператора меньше
{
    return this->name < other.name;
}

bool Database::operator>(const Database &other) const // перегрузка оператора больше
{
    return this->name > other.name;
}

int to_int(string str) // функция преведения строки в целочисленный тип
{
    int num = 0;
    for (int i = 0; i < str.length(); i++)
    {
        num += pow(10, str.length() - 1 - i) * (str[i] - '0');
    }
    return num;
}
uint devide(string &buf) // функция разделения строки
{
    uint num = 0;
    string temp;
    int i = 0;
    for (; buf[i]; i++)
    {
        if (buf[i] != '.')
            temp += buf[i];
        else
            break;
    }
    buf.erase(0, i + 1);
    num = to_int(temp);
    return num;
}

template <typename type>
type InputData(ifstream &in) // функция ввода данных с потока
{
    type data;
    in >> data;
    return data;
}

template <typename type>
type InputData()
{
    type data;
    cin >> data;
    return data;
}
string InputData(ifstream &in) // падумаць як перара
{
    string data;
    getline(in, data);
    return data;
}

int Database::DateCompare(string date) // -1 : this > date; 1: this>date; 0: this==date
{                                      // функция сравнинвания дат
    Database temp;
    temp.SetDate(date);
    if (this->date.year < temp.date.year)
        return 1;
    else if (this->date.year > temp.date.year)
        return -1;
    if (this->date.month < temp.date.month)
        return 1;
    else if (this->date.month > temp.date.month)
        return -1;
    if (this->date.day < temp.date.day)
        return 1;
    else if (this->date.day > temp.date.day)
        return -1;

    return 0;
}