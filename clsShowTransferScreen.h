#pragma once
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
class clsShowTransferScreen:protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient client)
	{
		cout << "Client card :" << endl;
		cout << "-------------------------------" << endl;
		cout << "Full name:" << client.FullName() << endl;
		cout << "Acc.Number:" << client.getAccountNumber() << endl;
		cout << "Balance:" << client.AccountBalance << endl;
		cout << "-------------------------------" << endl;
	}

	

public:
	static void showTransferMoneyScreen()
	{
		_DrawScreenHeader("Transfer money Screen");
		cout << "please enter account number to transfer from";
		string sourceAccountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(sourceAccountNumber))
		{
			cout << "Please enter account number again,this account isnt exist";
			 sourceAccountNumber = clsInputValidate::readString();
		}
		clsBankClient sourceClient = clsBankClient::findClient(sourceAccountNumber);

		_PrintClientCard(sourceClient);

		cout << "please enter account number to transfer to";
		string receiverAccountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(receiverAccountNumber))
		{
			cout << "Please enter account number again,this account isnt exist";
			 receiverAccountNumber = clsInputValidate::readString();
		}
		clsBankClient receiverClient = clsBankClient::findClient(receiverAccountNumber);
		_PrintClientCard(receiverClient);

		cout << "Enter transfer amount" << endl;
		double transferAmount = clsInputValidate::readDblNumber();


		char choice = 'N';
		cout << "Are you sure you want to perform this operation? Y|N" << endl;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			if (sourceClient.transferMoney(transferAmount, receiverClient))
			{

				cout << "Transfer done successfully" << endl;
				_PrintClientCard(sourceClient);
				cout << endl;
				_PrintClientCard(receiverClient);
			}
			else
			{
				cout << "there is an error occurred" << endl;
			}
		}
		else
		{
			cout << "The operation has canceled" << endl;
		}
	
			
		
		
	}
};