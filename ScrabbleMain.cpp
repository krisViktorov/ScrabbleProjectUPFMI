/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author <Kristian Viktorov>
* @idnumber 1MI0600187
* @compiler VC
*
* Main file for starting game
*
*/



#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <cstdlib>

using namespace std;
// swaps the values of two chars
void swap(char &a, char &b) {
	char temp = a;
	a = b;
	b = temp;
}

// converts all capital letters in string to lower case
void toLowerCase(string &str) {
	const int CASE_DIFF = 'a' - 'A';
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + CASE_DIFF;
		}
	}
}
// checks if entered word during game is consisted of the given letters
bool isWordValid(string enteredWord, char* letters, int lettersNumber) {
	if (enteredWord.length() > lettersNumber) { // checking if word has more letters than given
		return false;
	}

	bool letterAvaliable = false;
	for (int i = 0; i < enteredWord.length(); i++) {
		letterAvaliable = false;
		for (int j = i; j < lettersNumber; j++) {
			if (enteredWord[i] == letters[j]) {
				letterAvaliable = true;
				if (i != j) {
					swap(letters[j], letters[i]); // changing position of already used letter so we don't count it again
				}
				break;
			}
		}
		if (!letterAvaliable) {
			return false;
		}
	}
	return true;
}

// checks if letters can form a word from the dictionary
bool ableToFormWord(char* letters, int lettersNumber, set<string> dictionary) {
	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
		string word = *it;
		if (isWordValid(word, letters, lettersNumber)) {
			return true;
		}
	}
	return false;
}

int main() {

	// initial settings
	int rounds = 10;
	int givenLetters = 10;

	// copying words from dictionary file to a set of strings
	set<string> dictionary;
	ifstream readDictionary("dictionaryDemo.txt");
	if (!readDictionary) { // checking if file is successfully opened
		cout << "Error! Failed to open dictionary!" << endl;
		return 0; // ending program
	}
	string word;
	while (getline(readDictionary, word)) {
		dictionary.insert(word);
	}
	readDictionary.close();

	// creating a array containing letters from the alphabet
	const int ENGLISH_APLHABET_LETTERS = 26;
	char alphabet[ENGLISH_APLHABET_LETTERS] = {};
	char letter = 'a';
	for (int i = 0; i < ENGLISH_APLHABET_LETTERS; i++) {
		alphabet[i] = letter;
		letter++;
	}

	// Main menu
	while (true) { // while cycle for returning to start of menu
		cout << endl << "1. Start new game \n2. Settings \n3. Enter new word \n4. Exit \n"; // printing out main menu
		int menuChoice = 0;
		std::cin >> menuChoice;
		while (menuChoice < 1 || menuChoice>4) {
			cout << "Invalid input! Choose again!" << endl;
			std::cin >> menuChoice;
		}
		if (menuChoice == 1) {
			// New game
			int score = 0;
			// rounds
			for (int i = 1; i <= rounds; i++) {
				cout << endl << "ROUND " << i << ":" << endl;
				// giving out letters
				char* letters = new char[givenLetters];
				do {
					for (int j = 0; j < givenLetters; j++) {
						// selecting random letter from alphabet
						int alphabetIndex = rand() % ENGLISH_APLHABET_LETTERS;
						letters[j] = alphabet[alphabetIndex];
					}
				} while (!ableToFormWord(letters, givenLetters, dictionary));

				// printing out avaliable letters
				cout << "Avaliable letters:" << endl;
				for (int j = 0; j < givenLetters; j++) {
					cout << letters[j] << " ";
				}
				cout << endl;

				// entering word
				string enteredWord;
				do {
					cout << "Enter word:" << endl;
					getline(std::cin >> ws, enteredWord);
					toLowerCase(enteredWord);
				// checking if entered word is valid
				} while (!dictionary.count(enteredWord) || !isWordValid(enteredWord, letters, givenLetters)); 

				score = score + enteredWord.length(); // updating score after round end
				cout << enteredWord.length() << " points gained" << endl;
			}
			
			cout << endl << "Final score: " << score << endl;
			continue; // back to main menu
		}
		else if (menuChoice == 2) {
			// Settings
			cout << endl << "1. Change amount of letters given \n2. Change number of rounds \n3. Cancel \n"; // printing settings menu
			int settingChoice = 0;
			while (settingChoice < 1 || settingChoice > 3) {
				cout << "Invalid input! Choose again!" << endl;
				std::cin >> settingChoice;
			}
				if (settingChoice == 1) {
					// Change number of letters given
					cout << "Current number of letters given: " << givenLetters << endl
						<< "Enter numbers of letters to be given per round (3-30):" << endl;
					std::cin >> givenLetters;
					// valid value check
					while (givenLetters < 3 || givenLetters>30) {
						cout << "Invalid input! Try again!" << endl;
						std::cin >> givenLetters;
					}
					continue; // back to main menu
				}
				else if (settingChoice==2) {
					// change number of rounds
					cout << "Current number of rounds: " << rounds << endl
						<< "Enter number of rounds (1-100): " << endl;
					std::cin >> rounds;
					// valid value check
					while (rounds < 1 || rounds>100) {
						cout << "Invalid input! Try again!" << endl;
						std::cin >> rounds;
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
			cout << endl << "Enter new word: \n";
			getline(std::cin >> ws, newWord);
			toLowerCase(newWord);
			// Entering new word in dictionary
			ofstream writeInDictionary("dictionaryDemo.txt", ios::app);
			if (!writeInDictionary) { // checking if file is successfully opened
				cout << "Error! Failed to open dictionary!" << endl;
				return 0; // ending program
			}
			
			// check if word is already in dictionary
			if (dictionary.count(newWord)) {
				cout << "The word you entered is already in the dictionary" << endl;
			}
			else {
				writeInDictionary << endl << newWord;
				dictionary.insert(newWord);
				cout << "The new word has been put in the dictionary" << endl;
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