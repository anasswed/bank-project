#include<iostream>
#include"clsScreen.h";
#include"clsBankClient.h";
#include"clsInputValidate.h";
#pragma once
using namespace std;


class clsUpdateClientScreen :clsScreen
{
private :
	static void _ReadClientInfo(clsBankClient &client)
	{
		cout << "please enter first name" << endl;
		client.FirstName = clsInputValidate::readString();

		cout << "please enter last name" << endl;
		client.LastName = clsInputValidate::readString();

		cout << "please enter email" << endl;
		client.Email = clsInputValidate::readString();

		cout << "please enter phone" << endl;
		client.Phone = clsInputValidate::readString();

		cout << "please enter pin code" << endl;
		client.PinCode = clsInputValidate::readString();

		cout << "please enter Account balance" << endl;
		client.AccountBalance = clsInputValidate::readFltNumebr();
	}

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
	static void updateClient()
	{
		if (!checkAccessRight(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		_DrawScreenHeader("Update client screen");
	
		string accountNumber = "";
		cout << "please enter account number" << endl;
		accountNumber = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "Account number isnt found,choose another one" << endl;
			accountNumber = clsInputValidate::readString();
		}
		clsBankClient client1 = clsBankClient::findClient(accountNumber);
		_PrintClientInfo(client1);

		_ReadClientInfo(client1);

		clsBankClient::enSaveResults saveResult;
		saveResult = client1.saveResult();

		switch (saveResult)
		{
		case clsBankClient::enSaveResults::svFailedEmptyObject:
		{
			cout << "Error account was not saved because its empty" << endl;
			break;
		}
		case clsBankClient::enSaveResults::svSucceded: {
			cout << " Account updated successfully" << endl;
			client1.Print();
			break;
		}
		}



	}
};

