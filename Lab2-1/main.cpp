// Lab2-1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Runner.h"
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
		CheckParametrs(argc);
		CRunner application(argv[1], argv[2]);

		application.Run();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}


