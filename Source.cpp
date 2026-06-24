#include<iostream>
#include"clsBankClient.h";
#include"clsInputValidate.h";
#include"clsMainScreen.h";
#include<iomanip>
#include"clsLoginScreen.h"
using namespace std;

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}
	return 0;
}