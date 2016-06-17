#include <SFML/Graphics.hpp>
//#include "stdafx.h"
#include "main.h"

using namespace std;

void CheckParametrs(int argc)
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + to_string(AMOUNT_ARGUMENTS));
	}
}


int main(int argc, char *argv[]) 
{
	try
	{
		//CheckParametrs(argc);

		CApplication application;
		application.Run();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}
