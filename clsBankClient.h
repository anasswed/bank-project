#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include"clsPerson.h";
#include<string>
#include"clsString.h";
#include"clsDate.h"
#include"Global.h"


class clsBankClient :public clsPerson
{
private:
	enum enMode {
		emptyMode = 0, updateMode = 1, addNewMode = 2

	};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDeleted = false;

	static clsBankClient _ConvertLineToRecordObject(string line)
	{
		vector<string>vClient = clsString::Split(line, "#//#");
		return clsBankClient(enMode::updateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod (vClient[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient client,string seperator="#//#")
	{
		string clientRecord = "";

		clientRecord += client.FirstName + seperator + client.LastName + seperator + client.Email + seperator + client.Phone + seperator + client.getAccountNumber() + seperator + client.PinCode + seperator + to_string(client.AccountBalance);
		return clientRecord;
	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::emptyMode, "", "", "", "", "","",0);
	}
	static void _SaveClientDataToFile(vector<clsBankClient>vClients)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out);
		if (myFile.is_open())
		{
			string data = "";
			for (clsBankClient& client:vClients)
			{
				if (client._MarkedForDeleted == false) {
					data = _ConvertClientObjectToLine(client);
					myFile << data << endl;
				}
			}
			myFile.close();

		}
	}
	static vector<clsBankClient>_loadClientDataFromFileToVector()
	{
		vector<clsBankClient>_vClient;
		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsBankClient client = _ConvertLineToRecordObject(line);
				_vClient.push_back(client);
			}
			myFile.close();
			return _vClient;
		}
	}
	void _Update()
	{
		vector<clsBankClient>_vClient;
		_vClient = _loadClientDataFromFileToVector();

		for (clsBankClient& client : _vClient)
		{
			if (client.getAccountNumber() == getAccountNumber())
			{
				client = *this;
				break;
			}
		}
		_SaveClientDataToFile(_vClient);
	}
	void _AddDataLineToFile(string line)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out|ios::app);
		if (myFile.is_open())
		{
			myFile << line << endl;
			myFile.close();
		}
	}
	void _AddNewClient()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	 string _ConvertClientsOfTransferringToLine(clsBankClient receiverClient,double amount,string seperator="#//#")
	{
		return (clsDate::getCurrentTimeAndDate() + seperator +_AccountNumber + seperator +receiverClient.getAccountNumber()+seperator+ to_string(amount) + seperator + to_string(AccountBalance)+seperator + to_string(receiverClient.AccountBalance) +seperator+ currentUser.UserName);
	}

	void _SaveClientsOfTransferringToFile(clsBankClient receiverClient, double amount)
	{
		fstream MyFile;
		MyFile.open("TransferLogin.txt", ios::out | ios::app);

		string line = _ConvertClientsOfTransferringToLine(receiverClient, amount);
		if (MyFile.is_open())
		{
			MyFile << line << endl;
			MyFile.close();
		}

	}

	

public:
	clsBankClient(enMode mode, string firstName, string lastName, string email, string phone,string accountNumber, string pinCode, float accountBalance) :clsPerson(firstName,lastName,email,phone)
	{
		_Mode = mode;
		_AccountNumber = accountNumber;
		_AccountBalance = accountBalance;
		_PinCode = pinCode;
	}
	struct stClientData
	{
		string timeAndDate;
		string sourceAccountNumber;
		string receiverAccountNumber;
		double transferringAmount;
		double sourceAccountBalance;
		double receiverAccountBalance;
		string currentUser;


	};
	bool isMarkedToDelete()
	{
		return _MarkedForDeleted;
	}
	bool isEmpty()
	{
		return(_Mode == 0);
	}
	string getAccountNumber()
	{
		return _AccountNumber;
	}
	void setPinCode(string pinCode)
	{
		_PinCode = pinCode;
	}
	string getPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;
	void setAccountBalance(float accountBalance)
	{
		_AccountBalance = accountBalance;
	}

	float getAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	

	static clsBankClient findClient(string accountNumber)
	{
	
		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsBankClient client1 = _ConvertLineToRecordObject(line);
				if (client1.getAccountNumber() == accountNumber)
				{
					myFile.close();
					return client1;
				}
		
			}
			myFile.close();
		}
		return _GetEmptyClientObject();

	}

	static clsBankClient findClient(string accountNumber,string pinCode)
	{
	
		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsBankClient client1 = _ConvertLineToRecordObject(line);
				if (client1.getAccountNumber() == accountNumber && client1.PinCode== pinCode)
				{
					myFile.close();
					return client1;
				}
		
			}
			myFile.close();
		}
		return _GetEmptyClientObject();
		
	}

	static bool isClientExist(string accountNumber)
	{
		clsBankClient client1 = clsBankClient::findClient(accountNumber);
		return(!client1.isEmpty());
	}

	enum enSaveResults {
		svSucceded = 1, svFailedEmptyObject = 0, svfailedAccountNumberExis = 3
	};

	 enSaveResults saveResult()
	{
		 switch (_Mode)
		 {
		 case enMode::emptyMode: {

			 return enSaveResults::svFailedEmptyObject;
			 break;
		 }
		 case enMode::updateMode: {
			 _Update();
			 return enSaveResults::svSucceded;
			 break;
		 }
		 case enMode::addNewMode: {
			 if (isClientExist(_AccountNumber))
			 {
				 return enSaveResults::svfailedAccountNumberExis;
			 }
			 else
			 {

				 _AddNewClient();
			 }
			 break;
		 }
		 }
	}

	 bool Delete()
	 {
		 vector<clsBankClient>vClient;
		 vClient = _loadClientDataFromFileToVector();

		 for (clsBankClient &c : vClient)
		 {
			 if (c.getAccountNumber() == _AccountNumber)
			 {
				 c._MarkedForDeleted = true;
				 break;
			 }
		 }
		 _SaveClientDataToFile(vClient);
		 *this = _GetEmptyClientObject();
		 return true;
	 }

	static vector<clsBankClient> getClientsList()
	 {
		 return _loadClientDataFromFileToVector();
	 }

	static double getClientsBalances()
	{
		vector<clsBankClient>vClient = clsBankClient::getClientsList();
		double totalBalance = 0;

		for (clsBankClient &c : vClient)
		{
			totalBalance += c.AccountBalance;
		}
		return totalBalance;
	}

	void deposit(double amount)
	{
		_AccountBalance += amount;
		saveResult();
	}

	bool withdraw(double amount)
	{
		if (amount > AccountBalance)
		{
			return false;
		}
		else
		{
			
				AccountBalance -= amount;
				saveResult();
				return true;
		

			
		}
	}
	bool transferMoney(double amount, clsBankClient &receiverClient)
	{
		if (amount > AccountBalance)
		{
			return false;
		}
		else
		{
			withdraw(amount);
			receiverClient.deposit(amount);
			_SaveClientsOfTransferringToFile(receiverClient, amount);
			return true;
		}
	}

	static  stClientData convertClientDataOfTransferringToRecord(string line)
	{
		vector<string>vClientOfTransferring = clsString::Split(line, "#//#");
		stClientData clientsData;
		clientsData.timeAndDate = vClientOfTransferring[0];
		clientsData.sourceAccountNumber = vClientOfTransferring[1];
		clientsData.receiverAccountNumber = vClientOfTransferring[2];
		clientsData.transferringAmount = stoi(vClientOfTransferring[3]);
		clientsData.sourceAccountBalance = stoi(vClientOfTransferring[4]);
		clientsData.receiverAccountBalance = stoi(vClientOfTransferring[5]);
		clientsData.currentUser = vClientOfTransferring[6];
		return clientsData;

	}

	static vector<stClientData> getClientsOfTransferringList()
	{
		fstream MyFile;
		vector<stClientData>vClientData;
		MyFile.open("TransferLogin.txt", ios::in);
		stClientData clientsData;
		string line = "";
		if (MyFile.is_open())
		{
			while (getline(MyFile, line)) {
				clientsData = convertClientDataOfTransferringToRecord(line);
				vClientData.push_back(clientsData);
				MyFile.close();
			}
			return vClientData;
		}

	}

	 static clsBankClient getAddNewClientObject(string accountNumber)
	 {
		 return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0);
	 }

};

