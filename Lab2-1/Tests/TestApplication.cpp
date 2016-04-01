#include "stdafx.h"
#include "TestApplication.h"

BOOST_AUTO_TEST_SUITE(ApplicationTestModule)

// TODO: fix typo
bool TestApplictation(int argc, char *argv[])
{

	CApplication application(argc, argv);

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

	BOOST_CHECK_EQUAL_COLLECTIONS(iterResultFile, endIter, iterRightRsultFile, endIter);
};

BOOST_AUTO_TEST_CASE(Throw_exception_for_incorrect_data)
{
	char *arguments[] = { "Test.exe", "input0.txt" };
	BOOST_CHECK_THROW(TestApplictation(2, arguments), std::invalid_argument);

	char *arguments2[] = { "Test.exe", "input0.txt", "output1.txt", "m" };
	BOOST_CHECK_THROW(TestApplictation(4, arguments2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Throw_exception_for_nonexistent_file)
{
	char *arguments[] = { "Test.exe", "input-.txt", "output1.txt" };
	BOOST_CHECK_THROW(TestApplictation(3, arguments), std::ifstream::failure);
}

BOOST_AUTO_TEST_CASE(Throw_exception_for_incorrect_arguments)
{
	char *arguments[] = { "Test.exe", "input0.txt", "output1.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
}

BOOST_AUTO_TEST_CASE(Check_small_test_1)
{
	char *arguments[] = { "Test.exe", "input1.txt", "output1.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_CASE(Check_small_test_2)
{
	char *arguments[] = { "Test.exe", "input2.txt", "output2.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_CASE(Check_big_test_2)
{
	char *arguments[] = { "Test.exe", "inputBig.txt", "outputBig.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	//CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_SUITE_END()
