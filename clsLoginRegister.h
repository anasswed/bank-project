#pragma once
#include<vector>
#include"clsScreen.h"
#include"clsUser.h"
class clsLoginRegister :protected clsScreen
{
private:
    static void _PrintLoginRegisterLine(clsUser::stLoginRegister LoginRegisterRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(20) << left << LoginRegisterRecord.timeAndDate;
        cout << "| " << setw(20) << left << LoginRegisterRecord.userName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.password;
        cout << "| " << setw(20) << left << LoginRegisterRecord.permission;
    }

public:
	static void showLoginRegisterScreen()
	{
        if (!checkAccessRight(clsUser::enPermissions::pLoginRegisterUser))
        {
            return;
        }
        vector<clsUser::stLoginRegister>vLoginRegister = clsUser::getLoginRegisterList();
		_DrawScreenHeader("Login Register list screen",to_string(vLoginRegister.size()));

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(20) << "Time And Date";
        cout << "| " << left << setw(20) << "User name";
        cout << "| " << left << setw(20) << "password";
        cout << "| " << left << setw(20) << "permission";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegister.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else {
            for (clsUser::stLoginRegister user : vLoginRegister)
            {

                _PrintLoginRegisterLine(user);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

