#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"clsInputValidate.h";
class clsAddNewClientScreen :protected clsScreen
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

public:
	static void showAddNewClientScreen()
	{
		if (!checkAccessRight(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}
		_DrawScreenHeader("Add new client screen");
	

		string accountNumber = "";
		cout << "please enter account number" << endl;
		accountNumber = clsInputValidate::readString();

		while (clsBankClient::isClientExist(accountNumber))
		{
			cout << "please enter another account number is already exist" << endl;
			accountNumber = clsInputValidate::readString();

		}
		clsBankClient newClient = clsBankClient::getAddNewClientObject(accountNumber);
		_ReadClientInfo(newClient);
		clsBankClient::enSaveResults saveResult;
		saveResult = newClient.saveResult();

		switch (saveResult)
		{
		case clsBankClient::enSaveResults::svFailedEmptyObject:
		{
			cout << "Error account was not saved because its empty" << endl;
			break;
		}
		case clsBankClient::enSaveResults::svSucceded:
		{
			cout << " Client added successfully" << endl;
			newClient.Print();
			break;
		}
		case clsBankClient::enSaveResults::svfailedAccountNumberExis:
		{
			cout << "Account number is already exist so adding process has failed" << endl;
			break;
		}
		}
	}


};

