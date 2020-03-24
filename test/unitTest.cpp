#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Project1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PairUnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Proc p;
			string s = "2\nL 0 1 0 2\nL -1 1 -1 2";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);
			Assert::AreEqual(0, (int)result.size());
		}
		TEST_METHOD(TestMethod2)
		{
			Proc p;
			string s = "2\nL 99999 99999 -99999 -99999\nL 99999 99999 -99999 -99998";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);
			Assert::AreEqual(1, (int)result.size());
		}
		TEST_METHOD(TestMethod3)
		{
			Proc p;
			string s = "2\nL 99999 99999 -99999 -99999\nL -99998 99998 99998 -99998\n";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);
			Assert::AreEqual(1, (int)result.size());
		}
		TEST_METHOD(TestMethod4)
		{
			Proc p;
			string s = "4\nC 1 0 2\nC 2 2 1\nC 3 -2 6\nL -1 4 4 1";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(6, (int)result.size());
		}
		TEST_METHOD(TestMethod5)
		{
			Proc p;
			string s = "2\nC 0 0 2\nL 2 0 2 2";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(1, (int)result.size());
		}
		TEST_METHOD(TestMethod6)
		{
			Proc p;
			string s = "2\nC 0 0 2\nL 0 0 2 2";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(2, (int)result.size());
		}
		TEST_METHOD(TestMethod7)
		{
			Proc p;
			string s = "2\nC 0 0 2\nL 3 3 3 0";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(0, (int)result.size());
		}
		TEST_METHOD(TestMethod8)
		{
			Proc p;
			string s = "2\nC 0 0 2\nC 0 0 1";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(0, (int)result.size());
		}
		TEST_METHOD(TestMethod9)
		{
			Proc p;
			string s = "2\nC 0 0 2\nC 1 0 1";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(1, (int)result.size());
		}
		TEST_METHOD(TestMethod10)
		{
			Proc p;
			string s = "2\nC 0 0 2\nC 3 0 1";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(1, (int)result.size());
		}
		TEST_METHOD(TestMethod11)
		{
			Proc p;
			string s = "2\nC 0 0 2\nC 4 0 1";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(0, (int)result.size());
		}
		TEST_METHOD(TestMethod12)
		{
			Proc p;
			string s = "2\nC 0 0 2\nC 1 0 2";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(2, (int)result.size());
		}
		TEST_METHOD(TestMethod13)
		{
			Proc p;
			string s = "2\nC 0 0 2\nC 3 0 2";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(2, (int)result.size());
		}
		TEST_METHOD(TestMethod14)
		{
			//测试平行于x轴直线
			Proc p;
			string s = "2\nL 1 0 2 0\nL -1 1 -1 2";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(1, (int)result.size());
		}
		TEST_METHOD(TestMethod15)
		{
			//测试直线、线段、射线之间冲突
			Proc p;
			string s = "7\nL 1 3 4 2\nL -1 4 5 2\nS 2 4 3 2\nR 2 5 -1 2\nC 3 3 3\nC 2 2 1\nC 3 2 2";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(20, (int)result.size());
		}
		TEST_METHOD(TestMethod16)
		{
			//大型暴力测试
			Proc p;
			string s = "34\nL 1 3 4 2\nL -1 4 5 2\nS 2 4 3 2\nR 2 5 -1 2\nC 3 3 3\nC 2 2 1\nC 3 2 2\nL 99999 99999 -99999 -99999\nL -99998 99998 99998 -99998\nR 0 99 -1 100\nS 0 99 1 98\nS 2 97 1 98\nS 2 97 3 96\nS 4 95 3 96\nS 4 95 5 94\nS 6 93 5 94\nR 99 0 100 -1\nR 99 0 100 1\nR 0 -99 -1 -100\nS 0 -99 1 -98\nS 1 -98 2 -97\nS 99 0 98 -1\nS 3 -96 4 -95\nS 2 -97 3 -96\nS 99 0 98 1\nS 11 88 10 89\nS 12 87 11 88\nS 10000 10000 99999 10000\nS 10000 9999 10000 10000\nR 8888 8888 8888 8889\nS 1245 1245 1244 1247\nS 1244 1244 1243 1246\nS 2444 2444 2443 2447\nS 2442 2442 2443 2445\n\n\n\n\n\n\n\n";
			std::stringstream ss(s);
			p.process(ss);
			vector <pair<double, double>> result;
			p.getPointSet(result);

			Assert::AreEqual(54, (int)result.size());
		}
	};
}
