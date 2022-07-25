#include "main.hpp"
using namespace std;

int main()
{
    AccountingGoods system;
    try
    {
        system.Menu();
    }
    catch (string err)
    {
        cout << err << '\n';
    }
}