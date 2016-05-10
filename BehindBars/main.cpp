// Maximum cargo.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Runner.h"
#include "main.h"

/*
11.11. �� �������� (6)
��� ��������, ���� � ����, ����� � ��������. ������ ����� � ��������� 
������������� ������, ��� ����� ������� ��������, � ��������� 
���������� ��������. ����� ������� �������� ����� ���� �����. �������
����� ����� ������ ����������, � ���� ��������� ������� � ������� 
���, ����� ��������� �����. ����� �������� � ����� ���� ��� ����� 
���� (���� ���-����, ��� ��������� ����� ����), ���� ��������� ����� 
����� ��������� ����� �������, ���������� ����� �������� ����������.
���� �� ����� INPUT.TXT. � ������������ ������ �������� ����� ������ 
������ �����: ������� �������� ������ �������, ����� ������. ������ 
������� �������� ������������ ������ (x1, y1, x2, y2). ��� ����� 
�����, �� ������ �� ������ 10000.

����� � ���� OUTPUT.TXT. � ������������ ������ ������� ����������� 
����������, ������� ����� ���� ����� ����� � ������, ���� ������ 
����� ������ ����� ����� �������. ���������� ������ ���� �������� � 
����� ������� ����� �������.

������

����
0 1 0 5 1 -1 1 0

�����
1.414


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
		CRunner runner(argv[1], argv[2]);

		runner.Run();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}


