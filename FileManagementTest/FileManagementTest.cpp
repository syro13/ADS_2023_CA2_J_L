#include "pch.h"
#include "CppUnitTest.h"
#include "../FileManagementApp/XMLLoader.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace FileManagementTest
{
	TEST_CLASS(FileManagementTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			string fileName = "test.xml";
			XMLLoader<string> XMLFile(fileName);
			Assert::AreEqual(XMLFile.fileName->c_str(), fileName.c_str());
		}

		TEST_METHOD(TestLoad)
		{
			string fileName = "test.xml";
			XMLLoader<string> XMLFile(fileName);
			Assert::AreEqual(true, XMLFile.load());
		}
		TEST_METHOD(TestMakeTree)
		{
			string fileName = "test.xml";
			XMLLoader<string> XMLFile(fileName);
			XMLFile.load();
			XMLFile.makeTree();
			Assert::AreEqual(true, XMLFile.fileTree->count() > 0);

		}
	};
}
