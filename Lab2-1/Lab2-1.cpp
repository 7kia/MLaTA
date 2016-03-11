// Lab2-1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CApplication.h"


int main(int argc, char *argv[])
{
	CApplication application(argc, argv);

	bool isError = !application.Run();

	if (isError)
	{
		return 1;
	}

	return 0;
}


