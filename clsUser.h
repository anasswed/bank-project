#pragma once
#include<iostream>
#include<string>
#include"string.h";
#include"clsPerson.h";
#include "clsString.h"
#include <vector>
#include <fstream>
#include"clsDate.h";
#include"clsInputValidate.h"

using namespace std;
class clsUser :public clsPerson
{ 
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));

    }

    static string _ConvertUserObjectToLine(clsUser User,string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord +=User.Password + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }
    
     string _PrepareLoginRecord(string Seperator = "#//#")
    {
       
        string userRecord = "";
        userRecord =clsDate::getCurrentTimeAndDate()+Seperator+UserName+Seperator+Password+Seperator+to_string(Permissions);
        return userRecord;
    }


    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegisterUser = 128
    };

    struct stLoginRegister {
        string timeAndDate;
        string userName;
        string password;
        int permission;
    };
    
    clsUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string password, int permissions)
        :clsPerson(firstName, lastName, email, phone)
    {
        _Mode = mode;
        _UserName = userName;
        _Password = password;
        _Permissions = permissions;
    }

    bool isEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string getUserName()
    {
        return _UserName;
    }

    void setUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = getUserName, put = setUserName)) string UserName;

    void setPassword(string Password)
    {
        _Password = Password;
    }

    string getPassword()
    {
        return _Password;
    }
    __declspec(property(get = getPassword, put = setPassword)) string Password;

    void setPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int getPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

    static clsUser find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line)) 
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (isEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::isUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

    }
  

    static bool isUserExist(string UserName)
    {

        clsUser User = clsUser::find(UserName);
        return (!User.isEmpty());
    }

    bool deleteUser()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    static clsUser getAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> getUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool checkAccessPermession(enPermissions permission)
    {
        if (this->Permissions == enPermissions::eAll)
        {
            return true;
        }
        if ((permission & this->Permissions) == permission)
            return true;
        else
            return false;
    }

    void SaveLoginRegister()
    {

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out|ios::app);//overwrite

        string DataLine = "";

        if (MyFile.is_open())
        {





            DataLine = _PrepareLoginRecord();
            MyFile << DataLine;
            MyFile << endl;


            MyFile.close();

        }

    }

    static stLoginRegister _ConvertLoginRegisterLineToRecord(string line)
    {
        vector<string>vLoginRegister= clsString::Split(line, "#//#");
        stLoginRegister loginRegister;

        loginRegister.timeAndDate = vLoginRegister[0];
        loginRegister.userName = vLoginRegister[1];
        loginRegister.password =vLoginRegister[2];
        loginRegister.permission = stoi(vLoginRegister[3]);

        return loginRegister;
    }

    static vector<stLoginRegister> getLoginRegisterList()
    {
        vector<stLoginRegister>vLoginRegister;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);//

        if (MyFile.is_open())
        {
            string line = "";
            stLoginRegister loginRegisterRecord;

            while (getline(MyFile, line))
            {
                loginRegisterRecord = _ConvertLoginRegisterLineToRecord(line);
                vLoginRegister.push_back(loginRegisterRecord);
            }
            MyFile.close();
        }
        return vLoginRegister;
    }

};