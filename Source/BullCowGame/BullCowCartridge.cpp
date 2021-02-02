// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);    

    Isograms = GetValidWords(Words);
    InitGame();


    // PrintLine(TEXT("%i"), ValidWords.Num());

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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Words) const
{
    TArray<FString> ValidWords;
        for (FString Word : Words) {
            if (Word.Len() >= 4 
            && Word.Len() <= 8 
            && IsIsogram(Word)) {
                ValidWords.Emplace(Word);
            }
    }
    return ValidWords;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) 
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
        FBullCowCount Count = GetBullCows(Guess);

        PrintLine(TEXT("You have %i Bulls, and %i Cows!"), Count.Bulls, Count.Cows);

        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
    }
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString&  Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++) {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex]) {
            Count.Bulls++;
            continue;
        }
        
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++) {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex]) {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
    PrintLine(TEXT("%s"), *HiddenWord);
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