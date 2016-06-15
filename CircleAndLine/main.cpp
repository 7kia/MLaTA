// Maximum cargo.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Runner.h"
#include "main.h"

/*
11.13. Длина линии (6)
Имеется круг радиуса R с центром в начале координат. Заданы две точки (X1,Y1) и (X2,Y2). 
Требуется найти минимальную длину линии, соединяющей эти точки, но не пересекающей 
внутренность круга.

Ввод из файла INPUT.TXT. В первой строке находится целое число N – количество блоков 
входных данных. Далее  следуют N строк, каждая из которых содержит пять вещественных 
чисел через пробел – X1, Y1, X2, Y2 и R.

Вывод в файл OUTPUT.TXT. Для каждого блока входных данных выводится одно вещественное 
число с двумя знаками после запятой - минимальная длина линии.

Пример

Ввод
2
1 1 -1 -1 1
1 1 -1 1 1

Вывод
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


