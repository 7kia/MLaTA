#include "stdafx.h"
#include "RunnerTests.h"

BOOST_AUTO_TEST_SUITE(ApplicationTestModule)

bool TestApplictation(const std::string & nameInputFile, const std::string & nameOutputFile)
{
	CRunner application(nameInputFile, nameOutputFile);

	application.Run();

	return true;
}

const std::string PATH_RIGHT_DATA = "Right\\";

void CompareFiles(const std::string & first, const std::string & second)
{
	std::ifstream resultFile(first);
	std::ifstream rightResultFile(second);

	std::istream_iterator<char> iterResultFile(resultFile), endIter;
	std::istream_iterator<char> iterRightRsultFile(rightResultFile);

	//BOOST_CHECK_EQUAL_COLLECTIONS(iterResultFile, endIter, iterRightRsultFile, endIter);
	double firstNumber;
	double secondNumber;
	resultFile >> firstNumber;
	rightResultFile >> secondNumber;
	BOOST_CHECK_CLOSE(firstNumber, secondNumber, 4.f);
};

BOOST_AUTO_TEST_CASE(Throw_exception_for_nonexistent_file)
{
	BOOST_CHECK_THROW(TestApplictation("input-.txt", "output1.txt"), std::ifstream::failure);
}

BOOST_AUTO_TEST_CASE(Throw_exception_for_incorrect_arguments)
{
	BOOST_CHECK_THROW(TestApplictation("input0.txt", "output1.txt"), std::invalid_argument);
}

// 1
BOOST_AUTO_TEST_CASE(lines_is_parallel_and_is_parallel_to_y_axis___conectLine_not_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 2
BOOST_AUTO_TEST_CASE(lines_is_parallel_and_is_not_parallel_to_any_axis___conectLine_not_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 3
BOOST_AUTO_TEST_CASE(lines_is_parallel_and_is_parallel_to_y_axis___conectLine_is_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 4
BOOST_AUTO_TEST_CASE(lines_is_parallel_and_is_not_parallel_to_any_axis___conectLine_is_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 5
BOOST_AUTO_TEST_CASE(lines_is_parallel_and_is_parallel_to_y_axis_and_second_line_is_long___conectLine_is_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 6
BOOST_AUTO_TEST_CASE(lines_is_parallel_and_is_not_parallel_to_any_axis_and_second_line_is_long___conectLine_is_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 7
BOOST_AUTO_TEST_CASE(lines_is_perpendicular_but_not_connect_and_is_parallel_to_any_axis___conectLine_is_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 8
BOOST_AUTO_TEST_CASE(lines_is_perpendicular_but_not_connect_and_is_not_parallel_to_any_axis___conectLine_is_perpendicular)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 9
BOOST_AUTO_TEST_CASE(as_seventh_but_second_line_not_intersect_to_first)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 10
BOOST_AUTO_TEST_CASE(as_eighth_but_second_line_not_intersect_to_first)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 11
BOOST_AUTO_TEST_CASE(lines_intersect_to_one_point_and_first_line_is_parallel_to_y_axis)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 12
BOOST_AUTO_TEST_CASE(lines_intersect_to_one_point_and_lines_is_not_parallel_to_any_axis)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 13
BOOST_AUTO_TEST_CASE(lines_is_not_parallel_Second_line_is_parallel_to_y_axis)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 14
BOOST_AUTO_TEST_CASE(lines_is_not_parallel_and_is_not_parallel_to_any_axis)
{
	//std::string nameInputFile = "input1.txt";
	//std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(false);
	//CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

BOOST_AUTO_TEST_SUITE_END()
