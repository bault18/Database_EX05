#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
using namespace std;



void listAccess(string query, int input) {
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

	//~~~~~~~~~~~~~~~EDIT~~~~~~~~~~~~~~~~~~
	string stConnect = "DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:\\Users\\bault18\\Desktop\\NorthwindDatabase.accdb;UID=Admin;PWD=;";

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

	//Outpussing the columns
	for (int i = 0; i < 5; i++)
	{
		//1 col
		if (input == 3 || input == 4 || input == 5)
		{
			if (rc == SQL_SUCCESS) {
				rc = SQLFetch(hstmt);
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << endl;
			}
		}
		//2 col
		else if (input == 1 || input == 2)
		{
			if (rc == SQL_SUCCESS) {
				rc = SQLFetch(hstmt);
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << ", ";
				if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << endl;
			}
		}
		//3 col
		else if (input == 8)
		{
			if (rc == SQL_SUCCESS) {
				rc = SQLFetch(hstmt);
				if (SQLGetData(hstmt, 1, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << ", ";
				if (SQLGetData(hstmt, 2, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << ", ";
				if (SQLGetData(hstmt, 3, SQL_C_CHAR, szData, sizeof(szData), &cbData) == SQL_SUCCESS)
					cout << szData << endl;
			}
		}
	}
	cout << endl;

	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}


string EX01()
{
	string query = "SELECT P.[Product Name], (P.[list price] * 0.10) + P.[list price] AS New_List_Price ";
	query += "FROM Products AS P; ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Product Name, New list price: " << endl;
	return query;
}

string EX02()
{
	string query = "SELECT max(P.[target level]) AS Max_Target_Level, min(P.[target level]) AS Min_Target_Level, Avg(P.[target level]) AS Avg_Target_Level ";
	query += "FROM Products AS P; ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Max target level, Min target level, Avg target level: " << endl;
	return query;
}

string EX03()
{
	string query = "SELECT Count(*) AS Num_Discontinued ";
	query += "FROM Products AS P ";
	query += "WHERE P.[Discontinued] = YES; ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Num of discontinued items: " << endl;
	return query;
}

string EX04()
{
	string query = "SELECT [Product Name] ";
	query += "FROM Products ";
	query += "WHERE [Product Name] Like '*dried*'; ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Product name:" << endl;
	return query;
}

string EX05()
{
	string query = "SELECT [Product Name] ";
	query += "FROM Products ";
	query += "WHERE Discontinued = False AND Category = 'Beverages' ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Product name: " << endl;
	return query;
}

string EX08()
{
	string query = "SELECT O.[Shipped Date], E.[First name], E.[last name] ";
	query += "FROM Orders AS O, Employees AS E ";
	query += "WHERE O.[Employee ID] = E.ID; ";

	cout << "Query: " << query << endl << endl;
	cout << "Results: " << endl;
	cout << "Ship date, Employee Fname, Employee Lname: " << endl;
	return query;
}