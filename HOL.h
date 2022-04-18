#ifndef HOL_H
#define HOL_H

enum class Game {
	WIN = 1,
	LOOSE = 0,
};

int getRandomNumber(int min, int max);
int checkTemp();
Game highOrLow();
bool playAgain();
void theGreetings();
int checkBet(int balance);

#endif // !HOL_H
