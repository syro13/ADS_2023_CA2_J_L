#include "pch.h"
#include "CppUnitTest.h"
#include "../FileManagementApp/XMLLoader.h"
#include "../FileManagementApp/File.h"
#include "../FileManagementApp/Directory.h"
#include "../Trees/Tree.h"
#include "../Trees/TreeIterator.h"
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
			Assert::AreEqual(XMLFile.getFileName(), fileName);
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
			Assert::AreEqual(name, file.getName());
			Assert::AreEqual(length, file.getLength());
			Assert::AreEqual(type, file.getType());
		}
		TEST_METHOD(TestFileGetSetName) {
			string name = "testName";
			File file = File();
			file.setName(name);
			Assert::AreEqual(name, file.getName());
		}
		TEST_METHOD(TestFileGetSetLength) {
			string length = "testLength";
			File file = File();
			file.setLength(length);
			Assert::AreEqual(length, file.getLength());
		}
		TEST_METHOD(TestFileGetSetType) {
			string type = "testType";
			File file = File();
			file.setType(type);
			Assert::AreEqual(type, file.getType());
		}
		TEST_METHOD(TestDirectoryConstructor) {
			string name = "testName";
			Directory directory = Directory(name);
			Assert::AreEqual(name, directory.getName());
		}
		TEST_METHOD(TestDirectoryGetSetName) {
			string name = "testName";
			Directory directory = Directory();
			directory.setName(name);
			Assert::AreEqual(name, directory.getName());
		}
		TEST_METHOD(TestDirectoryAddFile) {
			string name = "testName";
			string length = "testLength";
			string type = "testType";
			File* file = new File(name, length, type);
			Directory directory = Directory();
			directory.addFile(file);
			Assert::AreEqual(name, directory.getFile(0)->getName());
			Assert::AreEqual(length, directory.getFile(0)->getLength());
			Assert::AreEqual(type, directory.getFile(0)->getType());
		}
		TEST_METHOD(TestDirectoryGetFile) {
			string name = "testName";
			string length = "testLength";
			string type = "testType";
			File* file = new File(name, length, type);
			Directory directory = Directory();
			directory.addFile(file);
			Assert::AreEqual(name, directory.getFile(0)->getName());
			Assert::AreEqual(length, directory.getFile(0)->getLength());
			Assert::AreEqual(type, directory.getFile(0)->getType());
		}
		TEST_METHOD(TestDirectoryGetFileCount) {
			string name = "testName";
			string length = "testLength";
			string type = "testType";
			File* file = new File(name, length, type);
			Directory directory = Directory();
			directory.addFile(file);
			Assert::AreEqual(1, directory.getFilesCount());
		}
		TEST_METHOD(TestDirectoryRemoveFileByName) {
			string name = "testName";
			string length = "testLength";
			string type = "testType";
			File* file = new File(name, length, type);
			Directory directory = Directory();
			directory.addFile(file);
			Assert::AreEqual(1, directory.getFilesCount());
			directory.removeFile("testName");
			Assert::AreEqual(0, directory.getFilesCount());
		}
		TEST_METHOD(TestDirectoryRemoveFileByFile) {
			string name = "testName";
			string length = "testLength";
			string type = "testType";
			File* file = new File(name, length, type);
			Directory directory = Directory();
			directory.addFile(file);
			Assert::AreEqual(1, directory.getFilesCount());
			directory.removeFile(file);
			Assert::AreEqual(0, directory.getFilesCount());
		}
	};
}
