#include "stdafx.h"
#include "TestApplication.h"

BOOST_AUTO_TEST_SUITE(ApplicationTestModule)

bool TestApplictation(const std::string & nameInputFile, const std::string & nameOutputFile)
{
	try
	{
		CRunner runner(nameInputFile, nameOutputFile);

		runner.Run();
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

BOOST_AUTO_TEST_CASE(Throw_exception_for_nonexistent_file)
{
	BOOST_CHECK(TestApplictation("input-.txt", "output1.txt") == false);
}

BOOST_AUTO_TEST_CASE(Check_small_test_1)
{
	std::string arguments[2] = { "inputSmall1.txt", "outputSmall1.txt" };
	BOOST_CHECK(TestApplictation(arguments[0], arguments[1]));
	CompareFiles(arguments[1], PATH_RIGHT_DATA + arguments[1]);
}

BOOST_AUTO_TEST_CASE(Check_small_test_2)
{
	std::string arguments[2] = { "inputSmall2.txt", "outputSmall2.txt" };
	BOOST_CHECK(TestApplictation(arguments[0], arguments[1]));
	CompareFiles(arguments[1], PATH_RIGHT_DATA + arguments[1]);
}

BOOST_AUTO_TEST_CASE(Check_small_test_3)
{
	std::string arguments[2] = { "inputSmall3.txt", "outputSmall3.txt" };
	BOOST_CHECK(TestApplictation(arguments[0], arguments[1]));
	CompareFiles(arguments[1], PATH_RIGHT_DATA + arguments[1]);
}

BOOST_AUTO_TEST_CASE(Check_middle_test_1)
{
	std::string arguments[2] = { "inputMiddle1.txt", "outputMiddle1.txt" };
	BOOST_CHECK(TestApplictation(arguments[0], arguments[1]));
	CompareFiles(arguments[1], PATH_RIGHT_DATA + arguments[1]);
}

BOOST_AUTO_TEST_CASE(Check_middle_test_2)
{
	std::string arguments[2] = { "inputMiddle2.txt", "outputMiddle2.txt" };
	BOOST_CHECK(TestApplictation(arguments[0], arguments[1]));
	CompareFiles(arguments[1], PATH_RIGHT_DATA + arguments[1]);
}

BOOST_AUTO_TEST_CASE(Check_big_test)
{
	std::string arguments[2] = { "inputBig.txt", "outputBig.txt" };
	BOOST_CHECK(TestApplictation(arguments[0], arguments[1]));
	CompareFiles(arguments[1], PATH_RIGHT_DATA + arguments[1]);
}

BOOST_AUTO_TEST_SUITE_END()
