#pragma once
#include"clsScreen.h";
#include"clsInputValidate.h";
#include"clsShowClientsList.h";
#include<iomanip>
#include"clsAddNewClientScreen.h";
#include"clsDeleteClient.h";
#include"clsUpdateClientScreen.h";
#include"clsFindClientScreen.h";
#include"clsTransactionScreen.h";
#include"clsManageUsersScreen.h";
#include"Global.h";
#include"clsLoginRegister.h"
#include"clsCurrencyScreen.h"
class clsMainScreen :protected clsScreen
{
private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eListLoginRegister = 8, eExit = 10, eCurrencyMainScrren = 9
	};
	static int _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		int Choice = clsInputValidate::readIntNumberBetween(1, 10, "Enter Number between 1 to 10 ? ");
		return Choice;
	}
	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenue();
	}
    static void _ShowAllClientsScreen()
    {
       
        clShowClientsList::showClientsList();

    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::showAddNewClientScreen();

    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClient::_DeleteClient();

    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::updateClient();

    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::FindClient();

    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionScreen::ShowTransactionsMenue();

    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }
    static void _ShowRegisterLoginScreen()
    {
        clsLoginRegister::showLoginRegisterScreen();
    }

    static void _ShowEndScreen()
    {
        currentUser = clsUser::find("", "");
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _ShowEndScreen();

            break;

        case enMainMenueOptions::eListLoginRegister:
        {
            system("cls");
            _ShowRegisterLoginScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eCurrencyMainScrren:
        {
            system("cls");
            clsCurrencyScreen::showCurrencyScreen();
            _GoBackToMainMenue();
            break;
        }
        }

    }
    public:
        static void ShowMainMenue()
        {

            system("cls");
            _DrawScreenHeader("\t\tMain Screen");
          
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Login users registered.\n";
            cout << setw(37) << left << "" << "\t[9] Currency Main scrren.\n";
            cout << setw(37) << left << "" << "\t[10] Logout.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
        }

};

