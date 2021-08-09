#include <iostream>
#include "Document.h"
#include "DocumentParser.h"
#include <thread>
#include <exception>

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "");
	//std::string pathDoc1 = argv[0];
	//std::string pathDoc2 = argv[1];

	std::string pathDoc1 = "C:\\Users\\valek\\Desktop\\doc1.txt";
	std::string pathDoc2 = "C:\\Users\\valek\\Desktop\\doc2.txt";

	//std::cout << "Input 2 text files: ";
	//std::cin >> pathDoc1 >> pathDoc2;
	std::string pathDoc3 = "C:\\Users\\valek\\Desktop\\Random-doc1.txt";
	std::string pathDoc4 = "C:\\Users\\valek\\Desktop\\Random-doc2.txt";

	Document doc1(pathDoc1);
	Document doc2(pathDoc2);

	Document doc3(pathDoc3);
	Document doc4(pathDoc4);
	
	try {

		std::thread thrd([&]() {
			DocumentParser parser;
			parser.StartParse(doc1, doc2);
			parser.StartObfuscating(doc1, doc2, doc3, doc4);
		});


		thrd.join();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
	
	return 1;

}


