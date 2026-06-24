#pragma once
#include<iostream>
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h";

using namespace std;
class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\t Current User : " << currentUser.UserName << endl;

        clsDate currentDate = clsDate::GetSystemDate();
        cout << "\t\t\t\t\t" << clsDate::DateToString(currentDate) << endl;
    }
    static bool checkAccessRight(clsUser::enPermissions permission)
    {
        if (!currentUser.checkAccessPermession(permission))
        {
            cout << " ---------------------------------------------" << endl;
            cout << "        Access denied contact your admin" << endl;
            cout << " ---------------------------------------------" << endl;
            return false;
        }
        else
            return true;
    }
    
};

