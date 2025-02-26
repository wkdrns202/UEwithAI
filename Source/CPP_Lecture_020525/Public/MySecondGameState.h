#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MySecondGameState.generated.h"

UCLASS()
class CPP_LECTURE_020525_API AMySecondGameState : public AGameState
{
	GENERATED_BODY()

public:
	AMySecondGameState();

	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	
	bool isHUDValid;

	UUserWidget* HUDWidget;
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;
	FTimerHandle HUDInitTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	void StartLevel();
	void OnLevelTimeUp();
	void OnCoinCollected();
	void EndLevel();
	UFUNCTION(Blueprintcallable, Category = "Score")
	void OnGameOver();
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(Blueprintcallable, Category = "Score")
	void AddScore(int32 Amount);

	void UpdateHUD();
	void UpdateHUDTime();
	void HUDValidCheck();
};
