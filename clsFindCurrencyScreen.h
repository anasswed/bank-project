#pragma once
#include"string.h"
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsCurrencies.h"
class clsFindCurrencyScreen:protected clsScreen
{
private:

	static void _PrintCurrencyInfo(clsCurrency currency)
	{
		
		cout << "currency card :" << endl;
		cout << "-------------------------------" << endl;
		cout << "Country :" << currency.Country();
		cout << "Code :" << currency.CurrencyCode();
		cout << "Name :" << currency.CurrencyName();
		cout << "Rate :" << currency.Rate();
		cout << "-------------------------------" << endl;
	}

	static int _ReadChoice()
	{
		cout << "Find by : [1] code or [2] country ?" << endl;
		int choice = clsInputValidate::readIntNumberBetween(1, 2, "please enter 1 or 2");
		return choice;

	}
public :
	static void showFindCurrencyScreen()
	{
		_DrawScreenHeader("Find Currency Screen");

		int choice = _ReadChoice();
		if (choice == 1)
		{
			cout << "please enter currency code" << endl;
			string code = "";
			cin >> code;
			while (!clsCurrency::IsCurrencyExist(code))
			{
				cout << "code isnt exist please enter code again" << endl;
				cin >> code;
			}
			cout << "currency found :)" << endl;

			clsCurrency currency = clsCurrency::FindByCode(code);
			_PrintCurrencyInfo(currency);
		}

		else
		{
			cout << "please enter name of the country" << endl;
			string country = "";
			cin >> country;

			clsCurrency currency = clsCurrency::FindByCountry(country);
			while (currency.IsEmpty())
			{
				cout << "currency wasnt found ):" << endl;
				cout << "please enter name of the country again" << endl;
				cin >> country;

				currency = clsCurrency::FindByCountry(country);

			}
			cout << "currency found :)" << endl;
			_PrintCurrencyInfo(currency);
		}
	}
};

