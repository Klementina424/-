#include "pch.h"
#include "CppUnitTest.h"
#include "C:/Users/79825/Desktop/modak/аисдКурс/duaList.cpp"
#include "C:/Users/79825/Desktop/modak/аисдКурс/calculator.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestКурс
{
	TEST_CLASS(CalculatorTest)
	{
		calculator Test;
		TEST_METHOD(plus)//мое
		{
			string res = "+ 2 2";
			Test.make_prefix("2+2");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(minus)//мое
		{
			string res = "- 2 2";
			Test.make_prefix("2-2");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(multiply)//мое
		{
			string res = "* 2 2";
			Test.make_prefix("2*2");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(divide)//мое
		{
			string res = "/ 2 2";
			Test.make_prefix("2/2");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(trigan)//мое
		{
			string res = "+ sin(pi) arccos(pi)";
			Test.make_prefix("sin(pi) + arccos(pi)");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(brackets)//мое
		{
			string res = "arcsin(/ pi 2)";
			Test.make_prefix("arcsin(pi/2)");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(mix)//мое
		{
			string res = "* + 1 sin(pi) - 1 cos(pi)";
			Test.make_prefix("(1+sin(pi))*(1-cos(pi))");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(unary_minus)//мое
		{
			string res = "- 0 -2";
			Test.make_prefix("-(-2)");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(unary_sum)//мое
		{
			string res = "- 0 + 1 2";
			Test.make_prefix("-(1+2)");
			Assert::AreEqual(Test.print_prefix(), res);
		}
	};

	TEST_CLASS(Calculator_Test)
	{
		calculator test;
		TEST_METHOD(sum)//мое
		{
			test.make_prefix("2+2");
			string result = "4.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(difference)//мое
		{
			test.make_prefix("2-2");
			string result = "0.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(composition)//мое
		{
			test.make_prefix("2*2");
			string result = "4.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(division)//мое
		{
			test.make_prefix("2/2");
			string result = "1.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(sum_brackets)//мое
		{
			test.make_prefix("(2-1)+(2-1)");
			string result = "2.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(trigonometry)//мое
		{
			test.make_prefix("cos(pi)");
			string result = "-1.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(sqrt)//мое
		{
			test.make_prefix("sqrt(4)");
			string result = "2.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(logarithm)//не работает
		{
			test.make_prefix("ln(e)");
			string result = "1.000000";
			Assert::AreEqual(test.get_result(), result);
		}
	};
	
	TEST_CLASS(UnitTestКурс)
	{
	public:
		duaList Empty;
		TEST_METHOD(Empty_test)
		{
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(Get_Size_test)
		{
			size_t real_size = 0;
			Assert::AreEqual(Empty.get_size(), real_size);
		}
		
		TEST_METHOD(Pop_Back_test)
		{
			Empty.pop_back();
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(insert_test)
		{
			try
			{
				Empty.insert("2", 0);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Incorrect index.", error);
			}
		}
		TEST_METHOD(remove_test)
		{
			try
			{
				Empty.remove(2);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Incorrect index.", error);
			}
		}
		TEST_METHOD(Pop_Front_test)
		{
			Empty.pop_front();
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(Clear_test)
		{
			Empty.clear();
			size_t real_size = 0;
			Assert::AreEqual(Empty.get_size(), real_size);
		}
		TEST_METHOD(Push_Back_test)
		{
			Empty.push_back("5");
			string str = "5";
			Assert::AreEqual(Empty.at(0), str);
			Empty.pop_back();
		}
		TEST_METHOD(Push_Front_test)
		{
			Empty.push_front("0");
			string str = "0";
			Assert::AreEqual(Empty.at(0), str);
		}
	};
}
