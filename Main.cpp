#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <random>

int main() {
	const int AMOUNT_OF_PROBLEMS = 5; //amount of problems to test
	//define path in main scope
	std::string QuestionsPath = ""; 
	std::string OutputPath = ""; //the teacher file will be placed in the same folder as the questions file
	while (true) {
		//get the questions beacuse your temp could be diffrent than mine
		std::cout << "Where is your questions file located?\n";
		std::getline(std::cin, QuestionsPath);

		//check if the file exist
		std::ifstream ifs(QuestionsPath);
		if (ifs) {
			ifs.close();
			break;
		}
		else {
			std::cout << "Not a valid path, try again.\n";
		}
	}

	OutputPath = QuestionsPath.substr(0, QuestionsPath.find_last_of('\\') + 1) + "output.txt";//makes the new file path in the same folder

	std::cout << "Reading file...\n";
	std::string linebuf;//line buffer
	std::vector<std::string> all_problems;//holds all the problems in an easy to iterate fasion
	std::ifstream ifs(QuestionsPath);//open file
	//add data from file to the string vector (all_problems)
	while (getline(ifs, linebuf)) {
		all_problems.push_back(linebuf);
	}

	//random number generator for random questions
	std::random_device RandGen;
	std::mt19937 eng(RandGen()); //make the random number algorithm
	std::uniform_int_distribution<int> range(1, all_problems.size() - 1); //make sure to get all the problems without going over

	//inform the user the program is ready
	std::cout << "\n\nYou will be solving " << AMOUNT_OF_PROBLEMS << " problems today.\nGood Luck!\n\n";
	
	//get the out stream
	std::ofstream ofs(OutputPath);
	//internaly reuse eveything to avoid main scoped varables
	for (int x = 0; x < AMOUNT_OF_PROBLEMS; x++) {
		std::string linebuf = all_problems.at(range(eng)) + " = ";
		std::string mainline = linebuf;
		std::cout << linebuf.c_str();
		std::getline(std::cin, linebuf);
		mainline.append(linebuf);
		ofs << mainline.c_str() << "\n";
	}
	//close our file
	ofs.close();

	std::cout << "Your all done!\nHit enter to exit the program.";

	(void)_getch();
	return 0;
}