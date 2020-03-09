#include "pch.h"
#include "CppUnitTest.h"
#include "..\..\src\main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(1, 1, 0, 0);
			Assert::AreEqual(intersect.intersect(), 0);
		}
	};
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(0, 1, 1, 0);
			intersect.addLine(0, 1, 1, 1);
			Assert::AreEqual(intersect.intersect(), 3);
		}
	};
	TEST_CLASS(UnitTest3)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(0, 1, 1, 0);
			Assert::AreEqual(intersect.intersect(), 1);
		}
	};
	TEST_CLASS(UnitTest4)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(0, 0, 0, 1);
			intersect.addLine(0, 0, 1, -1);
			Assert::AreEqual(intersect.intersect(), 1);
		}
	};
	TEST_CLASS(UnitTest5)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(0, 0, 1, 1);

			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(0, 0, 1, 1);
			Assert::AreEqual(intersect.intersect(), 0);
		}
	};
	TEST_CLASS(UnitTest6)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 1, 1);
			intersect.addLine(1, 0, 0, 1);
			intersect.addLine(1, 2, 2, 0);
			Assert::AreEqual(intersect.intersect(), 3);
		}
	};
	TEST_CLASS(UnitTest7)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			Assert::AreEqual(intersect.intersect(), 0);
		}
	};
	TEST_CLASS(UnitTest8)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 0, 0);
			Assert::AreEqual(intersect.intersect(), 0);
		}
	};
	TEST_CLASS(UnitTest9)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 0, 1);
			int num = 5000;
			for (int i = 0; i < num; i++) {
				intersect.addLine(0, i, 1, i);
			}
			Assert::AreEqual(intersect.intersect(), num);
		}
	};
	TEST_CLASS(UnitTest10)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 0, 1);
			intersect.addLine(0, 0, 1, 0);
			intersect.addLine(0, 1, 1, 1);
			Assert::AreEqual(intersect.intersect(), 2);
		}
	};
	TEST_CLASS(UnitTest11)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 0, 1);
			intersect.addLine(1, 0, 1, 1);
			int num = 5000;
			for (int i = 0; i < num; i++) {
				intersect.addLine(0, i, 1, i);
			}
			Assert::AreEqual(intersect.intersect(), 2 * num);
		}
	};
	TEST_CLASS(UnitTest12)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addLine(0, 0, 0, 1);
			intersect.addLine(1, 0, 1, 1);
			int num = 500;
			for (int i = 0; i < num; i++) {
				intersect.addLine(0, i, 1, i);
			}
			for (int i = 0; i < num; i++) {
				intersect.addLine(i, 0, i, 1);
			}
			Assert::AreEqual(intersect.intersect(), num * num);
		}
	};
	TEST_CLASS(UnitTest13)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			int num = 1000;
			for (int i = 0; i < num; i++) {
				intersect.addLine(i, 0, i - 1, 1);
			}
			for (int i = 0; i < num; i++) {
				intersect.addLine(i, 0, i + 1, 1);
			}
			Assert::AreEqual(intersect.intersect(), num * num);
			cout << "flag" << intersect.intersect();
		}
	};
	TEST_CLASS(UnitTest14)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			intersect.addCmd("C 1 0 2");
			intersect.addCmd("C 2 2 1");
			intersect.addCmd("C 3 -2 6");
			intersect.addCmd("L -1 4 4 -1");
			Assert::AreEqual(intersect.intersect(), 6);
			cout << "flag";
		}

	};
	TEST_CLASS(UnitTest15)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Intersect intersect;
			int num = 5000;
			for (int i = 0; i < num; i++) {
				intersect.addCircle(i, 0, 1);
			}
			
			Assert::AreEqual(intersect.intersect(), 3 * num - 4);
			cout << "flag";
		}

	};

}
