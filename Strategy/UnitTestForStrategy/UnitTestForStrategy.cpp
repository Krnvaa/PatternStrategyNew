#include "pch.h"
#include "CppUnitTest.h"
#include "..\Strategy\Strategy.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStrategyPattern
{
	TEST_CLASS(UnitTestStrategyPattern)
	{
	public:

		//Test for the default constructor
		TEST_METHOD(DefaultConstructorTest)
		{

			ArrayContext * arr = new ArrayContext();
			Assert::IsNull(arr->getStrategy());
			Assert::AreEqual(0, arr->getSize());
			Assert::IsNull(arr->getArray());
		}

		//Test for a constructor with one parameter
		TEST_METHOD(OneParameterConstructorTest)
		{
			ArrayContext * arr = new ArrayContext(5);
			Assert::IsNull(arr->getStrategy());
			Assert::AreEqual(5, arr->getSize());
			Assert::IsNotNull(arr->getArray());
		}
		//A test for a constructor with a single parameter with a negative array length
		TEST_METHOD(NegativeLengthOneParameterConstructorTest)
		{
			try {
				ArrayContext arr(-5);
			}
			catch (std::invalid_argument& e) {
				Assert::AreEqual("Array length is a negative number", e.what());
			}
		}
		//Test for a constructor with two parameters
		TEST_METHOD(TwoParameterConstructorTest)
		{

			Print * s1 = new PrintOneByOne();
			ArrayContext * arr = new ArrayContext(5, s1);
			Assert::IsTrue(arr->getStrategy() == s1);
			Assert::AreEqual(5, arr->getSize());
			Assert::IsNotNull(arr->getArray());
		}
		//Test for a constructor with two parameters with a negative array length
		TEST_METHOD(NegativeLengthTwoParameterConstructorTest)
		{
			Print* s1 = new PrintOneByOne();
			try {
				ArrayContext arr(-5, s1);
			}
			catch (std::invalid_argument& e) {
				Assert::AreEqual("Array length is a negative number", e.what());
			}

		}
		//For simplicity in the implementation of the Strategy pattern, 
		//the array of numbers is filled in: in the i-th place in the array, the value of i
		TEST_METHOD(FillArrayTest)
		{
			ArrayContext * arr = new ArrayContext(6);
			arr->fillArray();
			for (int i = 0; i < arr->getSize(); i++) {
				Assert::AreEqual(i, arr->operator[](i));
			}
		}

		TEST_METHOD(SetStrategyTest)
		{
			ArrayContext* arr = new ArrayContext(5);
			Print* s1 = new PrintOneByOne();
			Print* s2 = new PrintNInLine(2);

			arr->setStrategy(s1);
			Assert::IsTrue(arr->getStrategy() == s1);

			arr->setStrategy(s2);
			Assert::IsTrue(arr->getStrategy() == s2);

		}

		//test for Test for the method(PrintOneByOne) of printing one element per line 
		TEST_METHOD(TestPrintOneByOne)
		{
			// Creating an ArrayContext class object with an array size of 3 and filling it in
			ArrayContext arr(3);
			arr.fillArray();
			// Creating an object of the PrintOneByOne class and using it as a strategy for the arr object
			Print *strategy = new PrintOneByOne();
			arr.setStrategy(strategy);
			// Creating a stringstream object to intercept the output to the console
			std::stringstream output;
			// Redirecting the output from the console to the output object
			std::streambuf* oldOutput = std::cout.rdbuf(output.rdbuf());

			arr.useStrategy();
			std::cout.rdbuf(oldOutput);
			string res = "0\n1\n2\n";
			Assert::AreEqual(res, output.str());
		}
		//Test for the method(PrintNInLine) of printing n elements in a line separated by a space 
		TEST_METHOD(TestPrintNInLine)
		{

			ArrayContext arr(5);
			arr.fillArray();
			Print *strategy = new PrintNInLine(2);
			arr.setStrategy(strategy);
			std::stringstream output;
			std::streambuf* oldOutput = std::cout.rdbuf(output.rdbuf());
			arr.useStrategy();
			std::cout.rdbuf(oldOutput);
			string res = "0 1 \n2 3 \n4 \n";
			Assert::AreEqual(res, output.str());
		}
		//A test for the method of printing n elements in a line separated by a space for the case 
		//when n is equal to the length of the array
		TEST_METHOD(TestPrintNInLineNEqLength)
		{

			ArrayContext arr(2);
			arr.fillArray();
			Print *strategy = new PrintNInLine(2);
			arr.setStrategy(strategy);
			std::stringstream output;
			std::streambuf* oldOutput = std::cout.rdbuf(output.rdbuf());
			arr.useStrategy();
			std::cout.rdbuf(oldOutput);
			string res = "0 1 \n\n";
			Assert::AreEqual(res, output.str());
		}
		//A test for the method of printing n elements in a line separated by a space for the case 
		//when n is greater than the length of the array
		TEST_METHOD(TestPrintNInLineNGrLength)
		{
			Print* s1 = new PrintOneByOne();
			ArrayContext arr(2);
			arr.fillArray();
			Print *strategy = new PrintNInLine(2);
			arr.setStrategy(strategy);

			try {
				arr.useStrategy();
			}
			catch (std::invalid_argument& e) {

				Assert::AreEqual("The number of array elements in a line when printing cannot be greater than the length of characters", e.what());
			}

		}

	};
}
