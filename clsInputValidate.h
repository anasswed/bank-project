#pragma once
#include"clsDate.h"
using namespace std;
class clsInputValidate
{
public:

	static bool isNumberBetween(short x, short y, short z)
	{
		return(y<x && z>x);
	}

	static bool isNumberBetween(float x, float y, float z)
	{
		return (x<y && z>y);
	}

	static bool isDateBetween(clsDate date, clsDate date1, clsDate date2)
	{
		if (clsDate::IsDate1BeforeDate2(date, date2) && clsDate::IsDate1AfterDate2(date, date1) || (clsDate::IsDate1BeforeDate2(date, date1) && clsDate::IsDate1AfterDate2(date, date2)))
		{
			return true;
		}

		else {
			return false;
		}

	}

	static int readIntNumber(string message)
	{
		int x;
		while (true)
		{
			cin >> x;
			if (!cin.fail()) {
				break;
			}
			else
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << message << endl;
			}
		}
		return x;
	}

	static double readDblNumber()
	{
		double x = 0;
		while (true)
		{
			cin >> x;
			if (!cin.fail()) {
				break;
			}
			else
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
			}
		}
		return x;
	}

	static int readIntNumberBetween(int x, int y, string message)
	{
		int number = 0;
		while (true)
		{
			cin >> number;
			if (number >= x && number<= y)
			{
				return number;
			}
			else
			{
				cout << message;
			}
		}
	}

	static double readDblNumberBetween(double x, double y, string message)
	{
		double number = 0;
		while (true)
		{
			cin >> number;
			if (number>=x && number<=y) {
				return number;

			}
			else
				cout << message;
		}
	}

	static bool isValidDate(clsDate date)
	{
		if (clsDate::IsValidDate(date))
		{
			return true;
		}
		else
			return false;

	}

	static string readString()
{
	string info="";
	getline(cin>>ws,info);
	return info;
}
static float readFltNumebr()
{
	float x=0;
	cin>>x;
	return x;
}

static string encrypt(string title,int key=2)
{
	
	for(int i=0; i<=title.length(); i++)
	{
		title[i]=char((int)title[i]+key);
	}
	
	return title;


}

static string decrypt (string title, int key=2)
{
	
	for(int i=0; i<=title.length(); i++)
	{
		
		title[i]=char((int)title[i]-key);		

	}

	return title;
	
}

};

