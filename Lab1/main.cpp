// Task1.cpp: определ€ет точку входа дл€ консольного приложени€.
//


/*
1.4. –еликтова€ роща (6)
¬ заповеднике растет роща реликтовых деревьев.
ƒл€ их защиты требуетс€ обнести рощу забором. Ќо дл€ обеспечени€
доступа к остальной территории заповедника площадь участка, 
окруженного забором, должна быть минимальной. ƒеревь€ растут 
точно в узлах координатной сетки на рассто€нии одного метра друг
от друга. Ћюбое из деревьев имеет хот€ бы одного соседа (с юга,
севера, востока или запада). «абор состоит из блоков длиной в 
один метр.

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

