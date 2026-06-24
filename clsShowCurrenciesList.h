#pragma once
#include"clsScreen.h"
#include"clsCurrencies.h"
#include<vector>
class clsShowCurrenciesList:protected clsScreen
{

private:
    static void _PrintCurrencyLine(clsCurrency currency)
    {

    
        cout << "| " << setw(30) << left << currency.Country();
        cout << "| " << setw(10) << left << currency.CurrencyCode();
        cout << "| " << setw(30) << left <<currency.CurrencyName();
        cout << "| " << setw(10) << left << currency.Rate();

    }

public:
	static void showListOfCurrencies()
	{
		vector<clsCurrency>vCurrencies = clsCurrency::GetCurrenciesList();
		_DrawScreenHeader("Currencies List Screen", to_string(vCurrencies.size()));

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
        cout << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(10) << "Code";
        cout << "| " << left << setw(30) << "Name";
        cout << "| " << left << setw(10) << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsCurrency& currency :vCurrencies)
            {

                _PrintCurrencyLine(currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
	}
};

