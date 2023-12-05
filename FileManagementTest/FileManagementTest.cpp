#include "pch.h"
#include "CppUnitTest.h"
#include "../FileManagementApp/XMLLoader.h"
#include "../FileManagementApp/File.h"
#include "../FileManagementApp/Directory.h"
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
		TEST_METHOD(TestFileConstructor) {
			string name = "testName";
			string length = "testLength";
			string type = "testType";
			File file = File(name, length, type);
			Assert::AreEqual(name.c_str(), file.getName().c_str());
			Assert::AreEqual(length.c_str(), file.getLength().c_str());
			Assert::AreEqual(type.c_str(), file.getType().c_str());
		}
		TEST_METHOD(TestFileGetSetName) {
			string name = "testName";
			File file = File();
			file.setName(name);
			Assert::AreEqual(name.c_str(), file.getName().c_str());
		}
		TEST_METHOD(TestFileGetSetLength) {
			string length = "testLength";
			File file = File();
			file.setLength(length);
			Assert::AreEqual(length.c_str(), file.getLength().c_str());
		}
		TEST_METHOD(TestFileGetSetType) {
			string type = "testType";
			File file = File();
			file.setType(type);
			Assert::AreEqual(type.c_str(), file.getType().c_str());
		}
		TEST_METHOD(TestDirectoryConstructor) {
			string name = "testName";
			Directory directory = Directory(name);
			Assert::AreEqual(name.c_str(), directory.getName().c_str());
		}
		TEST_METHOD(TestDirectoryGetSetName) {
			string name = "testName";
			Directory directory = Directory();
			directory.setName(name);
			Assert::AreEqual(name.c_str(), directory.getName().c_str());
		}
	};
}
