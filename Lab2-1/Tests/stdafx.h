// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <clocale>                     // ��� ������� ��������� ������

#include <cstdlib>
#include <windows.h>


#define BOOST_TEST_MODULE PriseTestModule
#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702)
#include <boost/test/unit_test.hpp>


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
#include <string>

static const int AMOUNT_ARGUMENTS = 3;
static const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";

bool CheckParametrs(const std::string & nameInputFile, const std::string & nameOutputFile);
