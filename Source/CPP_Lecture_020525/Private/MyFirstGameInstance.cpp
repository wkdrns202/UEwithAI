// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstGameInstance.h"

UMyFirstGameInstance::UMyFirstGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UMyFirstGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}