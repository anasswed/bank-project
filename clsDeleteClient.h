#pragma once
#include<iostream>
#include"clsBankClient.h";
#include"clsScreen.h";
#include"clsInputValidate.h";
using namespace std;

class clsDeleteClient :protected clsScreen
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
	
public :
	static void _DeleteClient()
	{
		if (!checkAccessRight(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		_DrawScreenHeader("Delete client screen");
		

		string accountNumber = "";

		cout << "please enter account number" << endl;
		accountNumber = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "please enter account number again because client with this account number doesnt exist" << endl;
			accountNumber = clsInputValidate::readString();
		}
		clsBankClient client1 = clsBankClient::findClient(accountNumber);
		_PrintClientInfo(client1);

		cout << "Are you sure you want to delete this client" << endl;
		char answer = 'n';
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			if (client1.Delete())
			{
				cout << "client deleted successfully" << endl;
				_PrintClientInfo(client1);

			}
			else
			{
				cout << "!Error client wasnt deleted " << endl;
			}
		}
	}

};

