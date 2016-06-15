// Maximum cargo.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Runner.h"
#include "main.h"

/*
11.13. ����� ����� (6)
������� ���� ������� R � ������� � ������ ���������. ������ ��� ����� (X1,Y1) � (X2,Y2). 
��������� ����� ����������� ����� �����, ����������� ��� �����, �� �� ������������ 
������������ �����.

���� �� ����� INPUT.TXT. � ������ ������ ��������� ����� ����� N � ���������� ������ 
������� ������. �����  ������� N �����, ������ �� ������� �������� ���� ������������ 
����� ����� ������ � X1, Y1, X2, Y2 � R.

����� � ���� OUTPUT.TXT. ��� ������� ����� ������� ������ ��������� ���� ������������ 
����� � ����� ������� ����� ������� - ����������� ����� �����.

������

����
2
1 1 -1 -1 1
1 1 -1 1 1

�����
3.571
2.000

*/

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
		CRunner runner;

		runner.Run(argv[1], argv[2]);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}


