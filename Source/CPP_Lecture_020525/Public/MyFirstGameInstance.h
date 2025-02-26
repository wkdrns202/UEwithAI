#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyFirstGameInstance.generated.h"

UCLASS()
class CPP_LECTURE_020525_API UMyFirstGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyFirstGameInstance();

	UPROPERTY(VisibleAnywhere, BLueprintREadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BLueprintREadWrite, Category = "GameData")
	int32 CurrentLevelIndex;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
};
