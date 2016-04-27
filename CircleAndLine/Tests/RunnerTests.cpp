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

BOOST_AUTO_TEST_CASE(length_with_points_intersection)
{
	std::string nameInputFile = "input1.txt";
	std::string nameOutputFile = "output1.txt";
	BOOST_CHECK(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}

BOOST_AUTO_TEST_CASE(length_with_tangent)
{
	std::string nameInputFile = "input2.txt";
	std::string nameOutputFile = "output2.txt";
	BOOST_CHECK(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}


BOOST_AUTO_TEST_CASE(length_without_intersection)
{
	std::string nameInputFile = "input3.txt";
	std::string nameOutputFile = "output3.txt";
	BOOST_CHECK(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}
/*
BOOST_AUTO_TEST_CASE(Check_graph_with_several_loop)
{
	std::string nameInputFile = "input4.txt";
	std::string nameOutputFile = "output4.txt";
	BOOST_CHECK(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}


BOOST_AUTO_TEST_CASE(Check_big_test_2)
{
	std::string nameInputFile = "inputBig.txt";
	std::string nameOutputFile = "outputBig.txt";
	BOOST_CHECK(TestApplictation(nameInputFile, nameOutputFile));
	CompareFiles(nameOutputFile, PATH_RIGHT_DATA + nameOutputFile);
}
*/


BOOST_AUTO_TEST_SUITE_END()
