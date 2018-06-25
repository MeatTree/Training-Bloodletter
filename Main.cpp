/*	This is the console executable that makes use of the BullCow class
	This acts as the view in a MVC pattern and is responsible for all user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;	// instantiate a new game, which we re-use across plays



int main()	// entry point to app
{	
	do
	{
		std::cout << std::endl;
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());
	std::cout << "\nThanks for playing! BYE!!\n";
	return 0;	// exit application
}


void PrintIntro()
{
	std::cout << "\nWelcome to Bulls & Cows, a fun word game.\n\n";
	std::cout << "          }   {                ____            " << std::endl;
	std::cout << "          (o o)               (o  o)           " << std::endl;
	std::cout << "   /-------\\ /                 \\ /-------\\  " << std::endl;
	std::cout << "  / | BULL |O                   O|  COW | \\   " << std::endl;
	std::cout << " *  |-,----|                     |------|  *   " << std::endl;
	std::cout << "    ^      ^                     ^      ^      \n" << std::endl;
	std::cout << "A BULL is a correct letter in the correct position. A COW is a correct letter in the wrong position.\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	std::cout << "\n\n";
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
		{
			FText Guess = GetValidGuess();
			
			// submit valid guess to the game, and recieve counts
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

			std::cout << "	Bulls = " << BullCowCount.Bulls;
			std::cout << "\n	Cows = " << BullCowCount.Cows << "\n\n\n";
		}		
	PrintGameSummary();
	return;
}

// loop continually until user submits a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "\"" << Guess << "\" is not a valid isogram. An isogram is a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Only use lowercase letters!\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors
	return Guess;
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\n\nCongratulations! You WIN!\n\n";
	}
	else
	{
		std::cout << "\n\nYou LOSE! Better luck next time!\n\n";
	}
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
