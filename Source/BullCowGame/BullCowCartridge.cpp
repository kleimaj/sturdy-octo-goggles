// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

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
        ProcessGuess(Input);
    }

    
}

void UBullCowCartridge::ProcessGuess(FString Guess) 
{
    if (Guess == HiddenWord) {
        PrintLine(TEXT("Correct Word"));
        EndGame();
        return;
    }
    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("Sorry, try guessing again! \nThe Hidden Word is %i characters long!"), HiddenWord.Len());
        return;
    }
    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    // Check if Isogram
    --Lives;
    PrintLine(TEXT("You lost a life!"));
    if (Lives == 0) {
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
    }
    else {
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
    }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    int32 Len = Word.Len();
    for (int32 Index = 0; Index < Len; Index++) {
        for (int32 Comparison = Index + 1; Comparison < Len; Comparison++) {
            if (Word[Index] == Word[Comparison]) {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::InitGame() 
{
    PrintLine(TEXT("Welcome to Bull Cows!\n"));
    
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!\n"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives"), Lives);
    PrintLine(TEXT("Type in your guess. \nPress enter to continue..."));
}

void UBullCowCartridge::EndGame() 
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again!"));
}