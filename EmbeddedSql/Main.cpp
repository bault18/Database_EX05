#include <iostream>
#include <string>
#include "AcccesFunctions.h"
#include "SQLFunctions.h"
using namespace std;

int main()
{
	while (true)
	{
		cout << "Options: \n"
			<< "1) EX01 \n"
			<< "2) EX02 \n"
			<< "3) EX03 \n"
			<< "4) EX04 \n"
			<< "5) EX05 \n"
			<< "6) EX06 \n"
			<< "7) EX07 \n"
			<< "8) EX08 \n"
			<< "9) EX09 \n"
			<< "10) EX10 \n"
			<< "0) Exit \n"
			<< "\nUser Input: ";

		int input;
		cin >> input;

		system("cls");
		switch (input)
		{
			case 1: listAccess(EX01(), 1);
				break;
			case 2: listAccess(EX02(), 2);
				break;
			case 3: listAccess(EX03(), 3);
				break;
			case 4: listAccess(EX04(), 4);
				break;
			case 5: listAccess(EX05(), 5);
				break;
			case 6: listSQL(EX06(), 6);
				break;
			case 7: listSQL(EX07(), 7);
				break;
			case 8: listAccess(EX08(), 8);
				break;
			case 9: listSQL(EX09(), 9);
				break;
			case 10: listSQL(EX10(), 10);
				break;
			case 0: cout << "Exiting program" << endl;
				exit(1);
				break;
			default: cout << "\"" << input << "\" is an invalid input\n\n";
				break;

		}

		system("pause");
		system("cls");
	}
}
