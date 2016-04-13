// Task1.cpp: ���������� ����� ����� ��� ����������� ����������.
//


/*
1.4. ���������� ���� (6)
� ����������� ������ ���� ���������� ��������.
��� �� ������ ��������� ������� ���� �������. �� ��� �����������
������� � ��������� ���������� ����������� ������� �������, 
����������� �������, ������ ���� �����������. ������� ������ 
����� � ����� ������������ ����� �� ���������� ������ ����� ����
�� �����. ����� �� �������� ����� ���� �� ������ ������ (� ���,
������, ������� ��� ������). ����� ������� �� ������ ������ � 
���� ����.

*/

#include "stdafx.h"
#include "main.h"
#include "Runner.h"

void CheckParametrs(int argc)
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + std::to_string(AMOUNT_ARGUMENTS));
	}
}

int main(int argc , char *argv[])
{
	try
	{
		CheckParametrs(argc);

		CRunner runner(argv[1], argv[2]);

		runner.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}

