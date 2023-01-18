#include <iostream>
#include <string>
#include <fstream>
#include <set>



using namespace std;

int main() {
	// initial settings
	int rounds = 10;
	int givenLetters = 10;

	// copying words from dictionary file to a set of strings
	set<string> dictionary;
	ifstream readDictionary("dictionaryDemo.txt");
	if (!readDictionary) { // checking if file is successfully opened
		cout << "Error! Failed to open dictionary!";
		return 0; // ending program
	}
	string word;
	while (getline(readDictionary, word)) {
		dictionary.insert(word);
	}
	readDictionary.close();

	// Main menu
	while (true) { // while cycle for returning to start of menu
		cout << "1. Start new game \n 2. Settings \n 3. Enter new word \n 4. Exit \n"; // printing out main menu
		int menuChoice = 0;
		while (menuChoice < 1 || menuChoice>4) {
			cout << "Invalid input! Choose again! \n";
			cin >> menuChoice;
		}
		if (menuChoice == 1) {
			// New game
			int score = 0;

			continue; // back to main menu
		}
		else if (menuChoice == 2) {
			// Settings
			cout << "1. Change amount of letters given \n 2. Change number of rounds \n 3. Cancel \n"; // printing settings menu
			int settingChoice = 0;
			while (settingChoice < 1 || settingChoice > 3) {
				cout << "Invalid input! Choose again! \n";
				cin >> settingChoice;
			}
				if (settingChoice == 1) {
					// Change number of letters given
					cout << "Current number of letters given: " << givenLetters << "\n"
						<< "Enter numbers of letters to be given per round (3-30): \n";
					cin >> givenLetters;
					// valid value check
					while (givenLetters < 3 || givenLetters>30) {
						cout << "Invalid input! Try again!";
						cin >> givenLetters;
					}
					continue; // back to main menu
				}
				else if (settingChoice==2) {
					// change number of rounds
					cout << "Current number of rounds: " << rounds << "\n"
						<< "Enter number of rounds (1-100): \n";
					cin >> rounds;
					// valid value check
					while (rounds < 1 || rounds>100) {
						cout << "Invalid input! Try again!";
						cin >> rounds;
					}
					continue; // back to main menu
				}
				else {
					continue; // back to main menu
				}
		}
		else if (menuChoice == 3) {
			// New word
			string newWord;
			cout << "Enter new word: \n";
			getline(cin >> ws, newWord);

			// Entering new word in dictionary
			ofstream writeInDictionary("dictionaryDemo.txt");
			if (!writeInDictionary) { // checking if file is successfully opened
				cout << "Error! Failed to open dictionary!";
				return 0; // ending program
			}
			
			// check if word is already in dictionary
			if (dictionary.count(newWord)) {
				cout << "The word you entered is already in the dictionary";
			}
			else {
				writeInDictionary << endl << newWord;
				dictionary.insert(newWord);
			}
			writeInDictionary.close();
			continue; // back to main menu
		}
		else {
			// Exit
			return 0; // ending program
		}
	}
}