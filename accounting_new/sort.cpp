#pragma once
#include "accounting.cpp"

void Swap(Database &note1, Database &note2) // смена значений
{
    Database temp;
    temp = note1;
    note1 = note2;
    note2 = temp;
}

bool NameCompareDecrease(const Database &notes1, const Database &notes2) // сравнивание наименований в алфавитном порядке
{
    return notes1.GetName() < notes2.GetName();
}
bool NameCompareIncrease(const Database &notes1, const Database &notes2) // в не алфавитном порядке
{
    return notes1.GetName() > notes2.GetName();
}

bool PriceCompareDecrease(const Database &notes1, const Database &notes2) // сравнивание цены по убыванию
{
    return notes1.GetPrice() < notes2.GetPrice();
}
bool PriceCompareIncrease(const Database &notes1, const Database &notes2) // по возрастанию
{
    return notes1.GetPrice() > notes2.GetPrice();
}

bool AmountCompareDecrease(const Database &notes1, const Database &notes2) // сравнивание количества по убыванию
{
    return notes1.GetAmount() < notes2.GetAmount();
}
bool AmountCompareIncrease(const Database &notes1, const Database &notes2) // ао возрастанию
{
    return notes1.GetAmount() > notes2.GetAmount();
}

void QuickSort(vector<Database> &notes, bool (*Compare)(const Database &, const Database &),
               int left, int right) // сортировка базы данных
{
    Database mid = notes[((left + right) / 2)];
    int i = left;
    int j = right;
    do
    {
        while (Compare(notes[i], mid))
            i++;
        while (Compare(mid, notes[j]))
            j--;
        if (i <= j)
        {
            Swap(notes[i], notes[j]);
            i++;
            j--;
        }

    } while (i < j);
    if (left < j)
        QuickSort(notes, Compare, left, j);
    if (i < right)
        QuickSort(notes, Compare, i, right);
}