#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;



void listSQL(string query, int input) {
	const int MAX_DATA = 100;
	RETCODE rc;
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	char szData[MAX_DATA];
	string stSQL;
	SQLLEN cbData;
	char szPrice[10];

	

	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);

	SQLCHAR szConnectOut[1024];
	SQLSMALLINT cchConnect;

	//Check out http://www.devlist.com/ConnectionStringsPage.aspx for example connection strings
	string stConnect = "Driver={SQL Server};Server=CS1;";
	stConnect += "Database=Northwind;Trusted_Connection=yes;";


	
	stSQL = query;


	rc = SQLDriverConnect(hdbc, NULL, (SQLCHAR *)stConnect.c_str(), stConnect.length(), szConnectOut, 1024, &cchConnect, SQL_DRIVER_NOPROMPT);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, NULL, state, &code, error, 255, &cb);
		system("cls");
		cout << "ERROR!" << endl << error << endl;
		exit(0);
	}
	SQLAllocStmt(hdbc, &hstmt);


	rc = SQLExecDirect(hstmt, (SQLCHAR*)stSQL.c_str(), SQL_NTS);
	if (!(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO))
	{
		SQLTCHAR state[255], error[255];
		SQLINTEGER code;
		SQLSMALLINT cb;
		SQLError(henv, hdbc, hstmt, state, &code, error, 255, &cb);
		system("cls");
		cout << "ERROR!" << endl << error << endl;
		exit(0);
	}


	//Outputting the columns
	for (int i = 0; i < 5; i++)
	{
		//1 col
		if (input == 6)
		{
			if (rc == SQL_SUCCESS) {
				rc = SQLFetch(hstmt);
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << endl;
			}
		}

		//2 col
		else
		{
			if (rc == SQL_SUCCESS) {
				rc = SQLFetch(hstmt);
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << ", ";
				if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << ", ";
				if (SQLGetData(hstmt, 3, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData;
				cout << endl;
			}
		}

	}
	cout << endl;

	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}

string EX06()
{
	string query = "SELECT O.ShipName ";
	query += "FROM Orders O ";
	query += "WHERE O.Freight > 100; ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Ship Name:" << endl;
	return query;
}

string EX07()
{
	string query = "SELECT Firstname, LastName, Title ";
	query += "FROM Employees ;";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "First Name, Last name, Title:" << endl;
	return query;
}

string EX09()
{
	string query = "SELECT Max(UnitPrice) AS Max_Price, Min(UnitPrice) AS Min_Price, Avg(UnitPrice) AS Avg_Price ";
	query += "FROM Products ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Max Price, Min Price, Avg Price: " << endl;
	return query;
}

string EX10()
{
	string query = "SELECT CategoryID, Max(UnitPrice) AS Max_Price, Min(UnitPrice) AS Min_Price, Avg(UnitPrice) AS Avg_Price ";
	query += "FROM Products ";
	query += "GROUP BY CategoryID ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Category, Min Price, Avg Price: " << endl;
	return query;
}
