#pragma once
#include<iomanip>
#include<iostream>
#include"clsBankClient.h";
#include<vector>
#include"clsScreen.h";
using namespace std;
class clsShowClientsBalanceScreen :protected clsScreen
{
private:
	static void _PrintClientRecordBalanceLine(clsBankClient client)
	{
		cout << "| " << left << setw(15) << client.getAccountNumber();
		cout << "| " << left << setw(40) << client.GetFirstName() + client.GetLastName();
		cout << "| " << left << setw(12) << client.AccountBalance;

	}
public:
	static void showTotalBalance()
	{
		vector<clsBankClient>vClient = clsBankClient::getClientsList();
		string subTitle= "(" + to_string(vClient.size() )+"Clients";

		_DrawScreenHeader("Client's Total balances", subTitle);
		
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client name";
		cout << "| " << left << setw(12) << "Balance" << endl;
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		double totalBalance = clsBankClient::getClientsBalances();

		for (clsBankClient& c : vClient)
		{
			_PrintClientRecordBalanceLine(c);
			cout << endl;
		}
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		cout << "                                                                 Total Balance of all clients is " << totalBalance << endl;
	}
};

