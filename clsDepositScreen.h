#pragma once
#include<iostream>
#include"clsBankClient.h";
#include"clsScreen.h";
#include"clsInputValidate.h";
using namespace std;
class clsDepositScreen:protected clsScreen
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
	static void showDepositScreen()
	{
		_DrawScreenHeader("Deposit screen");
	
		string accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "Client with account number [" << accountNumber << "] doesnt exist" << endl;
			accountNumber = clsInputValidate::readString();
		}

		clsBankClient client = clsBankClient::findClient(accountNumber);

		_PrintClientInfo(client);

		double amount = 0;
		cout << "please enter deposit amount" << endl;
		amount = clsInputValidate::readDblNumber();

		cout << "Are you sure you want to perform this process" << endl;
		char choice = ' ';
		cin >> choice;

		if (choice == 'Y' || choice == 'y')
		{
			client.deposit(amount);
			cout << "Amount deposited successfully" << endl;
			cout << "New balance is " << client.AccountBalance;
		}
		else
			cout << "Operation canceled" << endl;
	}

};

