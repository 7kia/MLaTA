// LabPr1-1.cpp: ���������� ����� ����� ��� ����������� ����������.
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

