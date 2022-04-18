#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "HOL.h"


int checkTemp()
{
	while (true)
	{
		int temp;
		std::cin >> temp;

		// Проверка на предыдущее извлечение
		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else if ((temp > 100) || (temp < 0))
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << "Oops, Your number is out of range.  Please try again.\n";
		}
		else
		{
			std::cin.ignore(32767, '\n'); // удаляем лишние значения

			return temp;
		}
	}
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

Game highOrLow()
{
	std::cout << "I'm thinking of a number. You have 7 tries to guess what it is." << std::endl;
	int result = getRandomNumber(0, 100);
	for (int count = 1; count <= 7; count++) {
		std::cout << "Guess # " << count << ": " << std::endl;
		int temp = checkTemp();
		if (temp == result)
		{
			std::cout << "Correct! You win!" << std::endl;
			return (Game::WIN);
		}
		else if (temp < result)
			std::cout << "Your guess is too low." << std::endl;
		else if (temp > result)
			std::cout << "Your guess is too high." << std::endl;
	}
	std::cout << "Sorry, you lose. The correct number was " << result << "." << std::endl;
	return (Game::LOOSE);
}

bool playAgain()
{
	std::cout << "Would you like to play again (y/n)?" << std::endl;
	while (true) {
		char resultOfQestions;
		std::cin >> resultOfQestions;
		if ((resultOfQestions != 'y') && (resultOfQestions != 'n'))
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else if (resultOfQestions == 'y')
			return true;
		else if (resultOfQestions == 'n')
		{
			std::cout << "Thank you for playing." << std::endl;
			return false;
		}
	}
}

void theGreetings() {
	Sleep(1000);
	std::cout << "Let's play a game. You're have the 300$ dollars." << std::endl;
	Sleep(1000);
	std::cout << "Your task is to increase your balance.If your balance becomes zero, then you have lost." << std::endl;
	Sleep(1000);
}

int checkBet(int balance) {
	std::cout << "Enter your bet: ";
	while (true) {
		double bet;
		std::cin >> bet;
		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else if (bet > balance)
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << "Oops, You don't have that much money.  Please try again.\n";
		}
		else
		{
			std::cin.ignore(32767, '\n'); // удаляем лишние значения

			return bet;
		}
	}
}

int main()
{
	srand((static_cast<unsigned int>(time(0))));
	rand();

	theGreetings();

	int wins = 0;
	int defeats = 0;
	double balance = 300;

	do {
		int bet = checkBet(balance);
		Game resultOfHOL = highOrLow();
		if (resultOfHOL == Game::LOOSE) {
			defeats += 1;
			balance -= bet;
			if (balance == 0)
			{
				std::cout << "The result of the Game 'Hige or  Low' is: " << wins << "-wins and " << defeats << "-losses" << std::endl;
				exit(0);
			}
		}
		else if (resultOfHOL == Game::WIN)
		{
			wins += 1;
			balance *= 1.25;//koef of bet
			std::cout << "Your balance: " << balance << std::endl;
		}
	} while (playAgain() != false);

	std::cout << "The result of the Game 'Hige or  Low' is: " << wins << "-wins and " << defeats << "-losses" << std::endl;

	return 0;
}
