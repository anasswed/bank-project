#pragma once
#include"clsScreen.h";
#include"clsInputValidate.h";
#include"clsShowClientsList.h";
#include<iomanip>
#include"clsAddNewClientScreen.h";
#include"clsDeleteClient.h";
#include"clsUpdateClientScreen.h";
#include"clsDepositScreen.h";
#include"clsWithdrawScreen.h";
#include"clsShowClientsBalanceScreen.h";
#include"clsShowTransferScreen.h";
#include"clsMainScreen.h"
#include"clsTransactionLogScreen.h"

using namespace std;
class clsTransactionScreen : protected clsScreen
{ private:
    enum  enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 6, eShowTransfer = 4,
        eShowTransferLogScreen=5
	};
	static int _ReadTransactionMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";

		int choise = clsInputValidate::readIntNumberBetween(1, 6, "please enter a number between 1 & 6");
		return choise;
	}
	static void _ShowDepositScreen()
	{
        clsDepositScreen::showDepositScreen();
	}
	static void _ShowWithdrawScreen()
	{
        clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen()
	{
        clsShowClientsBalanceScreen::showTotalBalance();
	}
    static void _ShowTransferMoneyScreen()
    {
        clsShowTransferScreen::showTransferMoneyScreen();
    }
    static void _ShowTransferLogScreen()
    {
        clsTransactionLogScreen::showTransferLogScreen();
    }
	static void _ShowMainMenueScreen()
	{
      
	}
	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowTransactionsMenue();

	}
	
    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsMenueOptions::eShowTransfer:
        {
            system("cls");
            _ShowTransferMoneyScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsMenueOptions::eShowTransferLogScreen:
        {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
        }
       
        case enTransactionsMenueOptions::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }


    }

public:


    static void ShowTransactionsMenue()
    {
        if (!checkAccessRight(clsUser::enPermissions::pTranactions))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");
      

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer Money.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionMenueOption());
    }

};



