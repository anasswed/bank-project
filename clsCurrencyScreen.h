#pragma once
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsShowCurrenciesList.h";
#include"clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRate.h"
class clsCurrencyScreen:protected clsScreen
{
private:
    enum enCurrencyOption {
        eListCurrency = 1,
        eFindCurrency=2,
        eUpdateRate=3,
        eCurrencyCalculator=4,
        eShowMainMenue=5
    };

    static int _ReadCurrencyOption()
    {
        cout << setw(37) << left <<""<< "please choose what do you want to do [1-5]";
        int choice = clsInputValidate::readIntNumberBetween(1, 5, "please enter a number between 1-5");
        return choice;
    }
    static void _GoBackToCurrencyMainScree()
    {
        system("pause");
        showCurrencyScreen();
    }
    static void _PerformCurrencyScreenOption(enCurrencyOption currencyOption)
    {
        switch (currencyOption)
        {
        case enCurrencyOption::eListCurrency:
        {
            system("cls");
            clsShowCurrenciesList::showListOfCurrencies();
            _GoBackToCurrencyMainScree();
            break;
            
        }
        case enCurrencyOption::eCurrencyCalculator:
        {
            system("cls");
            clsFindCurrencyScreen::showFindCurrencyScreen();
            _GoBackToCurrencyMainScree();
            break;
        }
        case enCurrencyOption::eFindCurrency:
        {
            system("cls");
            clsUpdateCurrencyRate::showUpdateCurrencyRateScreen();
            _GoBackToCurrencyMainScree();
            break;

        }
        case enCurrencyOption::eUpdateRate:
        {
            system("cls");
        }
        case enCurrencyOption::eShowMainMenue:
        {

        }
        }
    }

public:
	static void showCurrencyScreen()
	{
		_DrawScreenHeader("Currency Exchange Main screen");

      

            system("cls");
            _DrawScreenHeader("\t\t Currency Exchange Main Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(30) << left << "" << "\t\t\tCurrency Exchange menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1]List currencies.\n";
            cout << setw(37) << left << "" << "\t[2] Find currencies.\n";
            cout << setw(37) << left << "" << "\t[3] Update rate.\n";
            cout << setw(37) << left << "" << "\t[4] Currency Calculator\n";
            cout << setw(37) << left << "" << "\t[5] Main menue.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerformCurrencyScreenOption((enCurrencyOption)_ReadCurrencyOption());
        
	}
};

