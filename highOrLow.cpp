#include <iostream>
#include <cstdlib>
#include <ctime>

enum class Game {
	WIN = 1,
	LOOSE = 0,
};

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
			std::cout << "Oops, that input is invalid.  Please try again.\n";
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

Game playGame()
{
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
	while(true) {
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

int main()
{
	srand((static_cast<unsigned int>(time(0))));
	rand();

	int wins = 0;
	int defeats = 0;

	do {
		Game playResult = playGame();
		if (playResult == Game::LOOSE)
			defeats += 1;
		else if (playResult == Game::WIN)
			wins += 1;
	}
	while (playAgain() != false);

	std::cout << "The result of the Game 'Hige or  Low' is: " << wins << "-wins and " << defeats << "-losses" << std::endl;

	return 0;
}
