#pragma once
#include"clsInputValidate.h"
#include"clsString.h"
#include"clsCurrencies.h"
#include"clsScreen.h"
#include<string>
class clsUpdateCurrencyRate:protected clsScreen
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
	static void _UpdateCurrencyRate(clsCurrency currency)
	{
		cout << "Update currency rate" << endl;
		cout << "--------------------------------" << endl;
		float rate = clsInputValidate::readFltNumebr();
		currency.UpdateRate(rate);
		
	}
public:
	static void showUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("Update Currency Rate Screen");

		cout << "please enter currency code " << endl;
		string code = clsInputValidate::readString();

		clsCurrency currency = clsCurrency::FindByCode(code);
		if (!currency.IsEmpty())
		{
			_PrintCurrencyInfo(currency);

			cout << "Are you sure you want to update this currency rate" << endl;
			char choice = 'Y';
			cin >> choice;
			if (tolower(choice)=='y')
			{
				_UpdateCurrencyRate(currency);
				cout << "Currency rate updated successfully" << endl;
				_PrintCurrencyInfo(currency);
			}
		}
		else
		{
			cout << "currency wasnt found" << endl;
		}
	}
};

