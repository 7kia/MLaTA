#include "stdafx.h"
#include "TestApplication.h"

BOOST_AUTO_TEST_SUITE(ApplicationTestModule)

bool TestApplictation(int argc, char *argv[])
{
	try
	{
		CApplication application(argc, argv);

		application.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
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

BOOST_AUTO_TEST_CASE(Throw_exception_for_incorrect_arguments)
{
	char *arguments[] = { "Test.exe", "input0.txt"};
	BOOST_CHECK(TestApplictation(2, arguments) == false);

	char *arguments2[] = { "Test.exe", "input0.txt", "output1.txt", "m" };
	BOOST_CHECK(TestApplictation(4, arguments2) == false);
}

BOOST_AUTO_TEST_CASE(Throw_exception_for_nonexistent_file)
{
	char *arguments[] = { "Test.exe", "input-.txt", "output1.txt" };
	BOOST_CHECK(TestApplictation(3, arguments) == false);
}

BOOST_AUTO_TEST_CASE(Check_small_test_1)
{
	char *arguments[] = { "Test.exe", "inputSmall1.txt", "outputSmall1.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_CASE(Check_small_test_2)
{
	char *arguments[] = { "Test.exe", "inputSmall2.txt", "outputSmall2.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_CASE(Check_small_test_3)
{
	char *arguments[] = { "Test.exe", "inputSmall3.txt", "outputSmall3.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_CASE(Check_middle_test_1)
{
	char *arguments[] = { "Test.exe", "inputMiddle1.txt", "outputMiddle1.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_CASE(Check_middle_test_2)
{
	char *arguments[] = { "Test.exe", "inputMiddle2.txt", "outputMiddle2.txt" };
	BOOST_CHECK(TestApplictation(3, arguments));
	CompareFiles(arguments[2], PATH_RIGHT_DATA + arguments[2]);
}

BOOST_AUTO_TEST_SUITE_END()
