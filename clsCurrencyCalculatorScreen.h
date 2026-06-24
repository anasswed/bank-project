#pragma once
#include"clsString.h"
#include"clsInputValidate.h"
#include"clsCurrencies.h"
#include"clsScreen.h"
class clsCurrencyCalculatorScreen:protected clsScreen
{

private:
	static void _PrintCurrencyInfo(clsCurrency currency)
	{

		cout << "-------------------------------" << endl;
		cout << "Country :" << currency.Country();
		cout << "Code :" << currency.CurrencyCode();
		cout << "Name :" << currency.CurrencyName();
		cout << "Rate :" << currency.Rate();
		cout << "-------------------------------" << endl;
	}

	static float _ReadAmountToExchange()
	{
		cout << "Enter amount to exchange" << endl;
		float amount = 0;
		cin >> amount;
		return amount;
	}
	static void _PerformCalculationBetweenTwoCurrency(float amount,clsCurrency currency1, clsCurrency currency2)
	{
		
			cout << "convert from" << endl;
			_PrintCurrencyInfo(currency1);
			float amountInUSD=currency1.convertToUSD(amount);
			cout << amount << currency1.CurrencyCode() << "=" << amountInUSD << currency2.CurrencyCode();

			if (currency2.CurrencyCode() == "USD")
			{
				return;
			}
			
	
			cout << "Converting from USD to" << endl;
			cout << "To :" << endl;
			_PrintCurrencyInfo(currency2);
			float convertFromUSDToAnother = currency1.convertFromUSDToAnother(amount, currency2);
			cout << amount << currency1.CurrencyCode() << "=" << convertFromUSDToAnother << currency2.CurrencyCode() << endl;
		

		
	}

	static clsCurrency _ReadCurrencyCode(string message)
	{
		cout << "message" << endl;
		string currencyCode = clsInputValidate::readString();

		while (!clsCurrency::IsCurrencyExist(currencyCode))
		{
			cout << "please enter currency code again because its not exist" << endl;
			currencyCode = clsInputValidate::readString();
		}
		clsCurrency currency = clsCurrency::FindByCode(currencyCode);
		return currency;

	}
public:
	static void showCurrencyCalculator()
	{
		char complete = 'y';
		while (complete == 'Y' || complete == 'y')
		{
			_DrawScreenHeader("Currency calculator screen");


			clsCurrency currency1 = _ReadCurrencyCode("please enter currency1 code");
			clsCurrency currency2 = _ReadCurrencyCode("please enter currency2 code");

			float amount = _ReadAmountToExchange();

			_PerformCalculationBetweenTwoCurrency(amount,currency1, currency2);

			cout << "Do you want to perform another calculation ? y\n" << endl;
			cin >> complete;
			
		
		}
	}
};

