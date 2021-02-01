// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows!\n"));
    PrintLine(TEXT("Guess the 4 letter word!\n")); // modularize this  into a variable
    PrintLine(TEXT("Press enter to continue..."));

    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    if (Input == HiddenWord) {
        PrintLine(TEXT("Correct Word"));
    }
    else {
        if (Input.Len() != HiddenWord.Len()) {
            PrintLine(TEXT("The Hidden Word is 4 characters long, try again!"));
        }
        PrintLine(TEXT("Incorrect Word"));
    }
}

void UBullCowCartridge::InitGame() 
{
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
}