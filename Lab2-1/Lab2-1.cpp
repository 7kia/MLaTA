// Lab2-1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CApplication.h"

using namespace std;

int main(int argc, char *argv[])
{

	try
	{
		CApplication application(argc, argv);

		application.Run();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}


