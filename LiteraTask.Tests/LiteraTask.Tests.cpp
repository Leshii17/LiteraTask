#include "pch.h"
#include "CppUnitTest.h"
#include "../LiteraTask/Document.h"
#include "../LiteraTask/DocumentParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LiteraTaskTests
{
	TEST_CLASS(LiteraTaskTests)
	{
	public:
		
		TEST_METHOD(TestExtracting)
		{
			std::string path = "C:\\Users\\valek\\Desktop\\TestDoc.txt";
			std::string expectedResult = "Montana enters this MOU in pursuant to its authority in USC28 §2-15-112(2) and 55!.";
			std::string outputRes;
			Document testDoc(path);
			DocumentParser testParser;
			
			testParser.StartExtracting(testDoc);
			for (auto x : testDoc.DocContent()) {
				outputRes += x + ' ';
			}
			
			Assert::AreEqual(expectedResult, outputRes);
		}
	};
}
