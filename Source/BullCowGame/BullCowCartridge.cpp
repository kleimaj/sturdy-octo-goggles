// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    InitGame();

    // PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord));    

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    // if game is over, then ClearScreen() and InitGame()
    if (bGameOver) {
        ClearScreen();
        InitGame();
    }
    else {
        if (Input == HiddenWord) {
            PrintLine(TEXT("Correct Word"));
            EndGame();
        }
        else {
            if (Input.Len() != HiddenWord.Len()) {
                PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
            }
            PrintLine(TEXT("Incorrect Word"));
            --Lives;
            if (Lives == 0) {
                EndGame();
            }
        }
    }

    
}

void UBullCowCartridge::InitGame() 
{
    PrintLine(TEXT("Welcome to Bull Cows!\n"));
    
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!\n"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess. \nPress enter to continue..."));
}

void UBullCowCartridge::EndGame() 
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again!"));
}