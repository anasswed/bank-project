#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h";
#include<vector>
class clsTransactionLogScreen :protected clsScreen
{
private:
    static void  printClientRecordLine(clsBankClient::stClientData clientData)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << clientData.timeAndDate;
        cout << "| " << setw(10) << left << clientData.sourceAccountNumber;
        cout << "| " << setw(10) << left << clientData.receiverAccountNumber;
        cout << "| " << setw(10) << left << clientData.transferringAmount;
        cout << "| " << setw(10) << left << clientData.sourceAccountBalance;
        cout << "| " << setw(10) << left << clientData.receiverAccountBalance;
        cout << "| " << setw(10) << left << clientData.currentUser;
    }
public:
	static void showTransferLogScreen()
	{
		vector<clsBankClient::stClientData>vTransferLog = clsBankClient::getClientsOfTransferringList();
		_DrawScreenHeader("Transfer log list screen", to_string(vTransferLog.size()));



        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Date/Time";
        cout << "| " << left << setw(8) << "S.AccountNumber";
        cout << "| " << left << setw(8) << "R.AccountNumber";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(8) << "S.Balance";
        cout << "| " << left << setw(8) << "D.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLog.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient::stClientData clientData : vTransferLog)
            {

                printClientRecordLine(clientData);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

