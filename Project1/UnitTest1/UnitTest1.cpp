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
			;
		}
	};

}
