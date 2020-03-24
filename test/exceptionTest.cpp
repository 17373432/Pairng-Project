#include "pch.h"
#include "CppUnitTest.h"
#include  <direct.h> 
#include  <stdio.h> 
#include "../src/Project1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PairProjectTest
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			int k;
			k = 0;
			try {
				k = core("exception1.txt");
			}
			catch (exception e) {
				Assert::AreEqual("N is out of range!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod2)
		{
			int k;
			k = 0;
			try {
				k = core("exception2.txt");
			}
			catch (exception e) {
				Assert::AreEqual("N is out of range!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod3)
		{
			int k;
			k = 0;
			try {
				k = core("exception3.txt");
			}
			catch (exception e) {
				Assert::AreEqual("The number of geometric objects is not equal to N!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod4)
		{
			int k;
			k = 0;
			try {
				k = core("exception4.txt");
			}
			catch (exception e) {
				Assert::AreEqual("The number of geometric objects is not equal to N!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod5)
		{
			int k;
			k = 0;
			try {
				k = core("exception5.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 3: \"L - 01 4 5 2\"\nThe format of input is illgal!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod6)
		{
			int k;
			k = 0;
			try {
				k = core("exception6.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 2: \"S 222222 4 3 2\"\nThe parameter(s) is(are) out of range!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod7)
		{
			int k;
			k = 0;
			try {
				k = core("exception7.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 2: \"s 2 4 3 2\"\nThe format of input is illgal!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod8)
		{
			int k;
			k = 0;
			try {
				k = core("exception8.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"C 3 3 3\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod9)
		{
			int k;
			k = 0;
			try {
				k = core("exception9.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"S 3 2 5 - 2\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod10)
		{
			int k;
			k = 0;
			try {
				k = core("exception10.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"S 11 0 5 2\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod11)
		{
			int k;
			k = 0;
			try {
				k = core("exception11.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"S - 1 2 - 4 - 1\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod12)
		{
			int k;
			k = 0;
			try {
				k = core("exception12.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"L 3 2 5 - 2\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod13)
		{
			int k;
			k = 0;
			try {
				k = core("exception13.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"L 11 0 5 2\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod14)
		{
			int k;
			k = 0;
			try {
				k = core("exception14.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"L - 1 2 - 4 - 1\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod15)
		{
			int k;
			k = 0;
			try {
				k = core("exception15.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"R 3 2 5 - 2\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod16)
		{
			int k;
			k = 0;
			try {
				k = core("exception16.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"R 11 0 5 2\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod17)
		{
			int k;
			k = 0;
			try {
				k = core("exception17.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 5: \"R - 1 2 - 4 - 1\"\nOverlap with added drawings!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod18)
		{
			int k;
			k = 0;
			try {
				k = core("exception18.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 4: \"C 2 5 - 1\"\nRadius of circle must be greater than zero!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod19)
		{
			int k;
			k = 0;
			try {
				k = core("exception19.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 4: \"C 2 5 0\"\nRadius of circle must be greater than zero!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod20)
		{
			int k;
			k = 0;
			try {
				k = core("exception20.txt");
			}
			catch (exception e) {
				Assert::AreEqual("The input file is empty!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod21)
		{
			int k;
			k = 0;
			try {
				k = core("exception21.txt");
			}
			catch (exception e) {
				Assert::AreEqual("Line 2: \"S 2 4 2 4\"\nThe two points coincide!\n", e.what());
			}
		}
		TEST_METHOD(TestMethod22)
		{
			int k;
			k = 0;
			try {
				k = core("exception22.txt");
			}
			catch (exception e) {
				Assert::AreEqual("The first line of input file is not a number!\n", e.what());
			}
		}
	};
}
