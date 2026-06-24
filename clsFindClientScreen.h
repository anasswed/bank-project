#pragma once
#include<iostream>
#include"clsBankClient.h";
#include"clsScreen.h";
#include"clsInputValidate.h";
using namespace std;

class clsFindClientScreen:protected clsScreen
{
private:
	static void _PrintClientInfo(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << client.FirstName;
		cout << "\nLastName    : " << client.LastName;
		cout << "\nFull Name   : " << client.FullName();
		cout << "\nEmail       : " << client.Email;
		cout << "\nPhone       : " << client.Phone;
		cout << "\nAcc. Number : " << client.getAccountNumber();
		cout << "\nPassword    : " << client.PinCode;
		cout << "\nBalance     : " << client.AccountBalance;
		cout << "\n___________________\n";
	}

public:
	static void FindClient()
	{
		if (!checkAccessRight(clsUser::pFindClient))
		{
			return;
		}
		_DrawScreenHeader("Find client screen");

		string accountNumber = "";
		accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << " account number :" << accountNumber << "doesnt found choose another one" << endl;
			accountNumber= clsInputValidate::readString();
		}
	
		clsBankClient client = clsBankClient::findClient(accountNumber);

		if (!client.isEmpty())
		{
			cout << "client found :)" << endl;

		}
		else
		{
			cout << "client doesnt found" << endl;
		}
		_PrintClientInfo(client);
	}
};

