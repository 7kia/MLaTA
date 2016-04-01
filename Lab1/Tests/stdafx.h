// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <clocale>                     // дл€ функций настройки локали

#include <cstdlib>
#include <windows.h>


#define BOOST_TEST_MODULE PriseTestModule
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702)
#include <boost/test/unit_test.hpp>


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
