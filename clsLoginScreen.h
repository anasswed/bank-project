#pragma once
#include"clsScreen.h";
#include"clsMainScreen.h";
#include"clsUser.h";
#include"clsInputValidate.h";
#include"Global.h"
class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short trial = 4;

        string Username, Password;
        do
        {
            trial--;
                if (LoginFaild)
                {
                    cout << "\nInvalid Username/Password!\n\n";
                    if (trial != 0) {
                        cout << "you have only " << trial << " trial" << endl;
                    }
                    else
                    {
                        cout << "You tried to enter to system 3 time so you blocked" << endl;
                        return false;
                    }
                    
                       
                }

                cout << "Enter Username? ";
                cin >> Username;

                cout << "Enter Password? ";
                cin >> Password;

                currentUser = clsUser::find(Username, Password);

                LoginFaild = currentUser.isEmpty();

        }while(LoginFaild);
        
        currentUser.SaveLoginRegister();
            clsMainScreen::ShowMainMenue();
            return true;
    }

public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }
};

