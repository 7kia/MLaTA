#include "stdafx.h"
#include "RunnerTests.h"

BOOST_AUTO_TEST_SUITE(ApplicationTestModule)

void TestApplictation(const std::string & nameInputFile, const std::string & nameOutputFile)
{
	CRunner application(nameInputFile, nameOutputFile);

	application.Run();
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
/*
BOOST_AUTO_TEST_CASE(Throw_exception_for_incorrect_arguments)
{
	BOOST_CHECK_THROW(TestApplictation("input0.txt", "output1.txt"), std::invalid_argument);
}
*/


// 1
BOOST_AUTO_TEST_CASE(_1___lines_is_parallel_and_is_parallel_to_y_axis___conectLine_not_perpendicular)
{
	std::string nameInputFile = "input1.txt";
	std::string nameOutputFile = "output1.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 2
BOOST_AUTO_TEST_CASE(_2___lines_is_parallel_and_is_not_parallel_to_any_axis___conectLine_not_perpendicular)
{
	std::string nameInputFile = "input2.txt";
	std::string nameOutputFile = "output2.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 3
BOOST_AUTO_TEST_CASE(_3___lines_is_parallel_and_is_parallel_to_y_axis___conectLine_is_perpendicular)
{
	std::string nameInputFile = "input3.txt";
	std::string nameOutputFile = "output3.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 4
BOOST_AUTO_TEST_CASE(_4___lines_is_parallel_and_is_not_parallel_to_any_axis___conectLine_is_perpendicular)
{
	std::string nameInputFile = "input4.txt";
	std::string nameOutputFile = "output4.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 5
BOOST_AUTO_TEST_CASE(_5___lines_is_parallel_and_is_parallel_to_y_axis_and_second_line_is_long___conectLine_is_perpendicular)
{
	std::string nameInputFile = "input5.txt";
	std::string nameOutputFile = "output5.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 6
BOOST_AUTO_TEST_CASE(_6___lines_is_parallel_and_is_not_parallel_to_any_axis_and_second_line_is_long___conectLine_is_perpendicular)
{
	std::string nameInputFile = "input6.txt";
	std::string nameOutputFile = "output6.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 7
BOOST_AUTO_TEST_CASE(_7___lines_is_perpendicular_but_not_connect_and_is_parallel_to_any_axis___conectLine_is_perpendicular)
{
	std::string nameInputFile = "input7.txt";
	std::string nameOutputFile = "output7.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 8
BOOST_AUTO_TEST_CASE(_8___lines_is_perpendicular_but_not_connect_and_is_not_parallel_to_any_axis___conectLine_is_perpendicular)
{
	std::string nameInputFile = "input8.txt";
	std::string nameOutputFile = "output8.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 9
BOOST_AUTO_TEST_CASE(_9___as_seventh_but_second_line_not_intersect_to_first)
{
	std::string nameInputFile = "input9.txt";
	std::string nameOutputFile = "output9.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 10
BOOST_AUTO_TEST_CASE(_10___as_eighth_but_second_line_not_intersect_to_first)
{
	std::string nameInputFile = "input10.txt";
	std::string nameOutputFile = "output10.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 11
BOOST_AUTO_TEST_CASE(_11___lines_intersect_to_one_point_and_first_line_is_parallel_to_y_axis)
{
	std::string nameInputFile = "input11.txt";
	std::string nameOutputFile = "output11.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 12
BOOST_AUTO_TEST_CASE(_12___lines_intersect_to_one_point_and_lines_is_not_parallel_to_any_axis)
{
	std::string nameInputFile = "input12.txt";
	std::string nameOutputFile = "output12.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 13
BOOST_AUTO_TEST_CASE(_13___lines_is_not_parallel_Second_line_is_parallel_to_y_axis)
{
	std::string nameInputFile = "input13.txt";
	std::string nameOutputFile = "output13.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

// 14
BOOST_AUTO_TEST_CASE(_14___lines_is_not_parallel_and_is_not_parallel_to_any_axis)
{
	std::string nameInputFile = "input14.txt";
	std::string nameOutputFile = "output14.txt";

	BOOST_CHECK_NO_THROW(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

BOOST_AUTO_TEST_SUITE_END()
