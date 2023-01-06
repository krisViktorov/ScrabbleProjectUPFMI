#include <iostream>

int main() {
	// Main menu
	std::cout << "1. Start new game \n 2. Settings \n 3. Enter new word \n 4. Exit \n";
	int menuChoice = 0;
	while (menuChoice < 1 || menuChoice>4) {
		std::cin >> menuChoice;
	}
	switch (menuChoice) {
	case 1:
		// New game
		break;
	case 2:
		// Settings
		std::cout << "1. Change amount of letters given \n 2. Change number of rounds";
		int settingChoice = 0;
		while (settingChoice != 1 && settingChoice != 2) {
			std::cin >> settingChoice;
			if (settingChoice == 1) {
				// Change number of letters given
			}
			else {
				// change number of rounds
			}
		}
		break;
	case 3:
		// New word
		break;
	case 4:
		// Exit
		break;
	}
}