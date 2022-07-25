#include "sort.cpp"
void Swap(Database &note1, Database &note2);
bool NameCompareDecrease(const Database &notes1, const Database &notes2);
bool NameCompareIncrease(const Database &notes1, const Database &notes2);
bool PriceCompareDecrease(const Database &notes1, const Database &notes2);
bool PriceCompareIncrease(const Database &notes1, const Database &notes2);
bool AmountComapreDecrease(const Database &notes1, const Database &notes2);
bool AmountComapreIncrease(const Database &notes1, const Database &notes2);
void QuickSort(vector<Database> &notes, bool (*compare)(const Database &, const Database &),
               int left, int right);
