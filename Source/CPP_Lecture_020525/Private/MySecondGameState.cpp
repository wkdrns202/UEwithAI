#include "MySecondGameState.h"
#include "Kismet/GameplayStatics.h"
#include "MyFirstPlayerController.h"
#include "SpawnVolume.h"
#include "MyFirstGameInstance.h"
#include "CoinItem.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AMySecondGameState::AMySecondGameState()
{
	// Init for All
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
	isHUDValid = false;
}
void AMySecondGameState::BeginPlay()
{
	Super::BeginPlay();
	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDInitTimerHandle,
		this,
		&AMySecondGameState::HUDValidCheck,
		0.2f,
		false
	);

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AMySecondGameState::UpdateHUDTime,
		0.1f,
		true
	);

	

}
int32 AMySecondGameState::GetScore() const
{
	return Score;
}
void AMySecondGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyFirstGameInstance* MyFirstGameInstance = Cast<UMyFirstGameInstance>(GameInstance);
		if (MyFirstGameInstance)
		{
			MyFirstGameInstance->AddToScore(Amount);
			UE_LOG(LogTemp, Warning, TEXT("Score %d"), Amount);
		}
	}
	
}
void AMySecondGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyFirstPlayerController* MyPlayerController = Cast<AMyFirstPlayerController>(PlayerController))
		{
			MyPlayerController->ShowGameHUD();
		}
	}


	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyFirstGameInstance* MyFirstGameInstance = Cast<UMyFirstGameInstance>(GameInstance);
		if (MyFirstGameInstance)
		{
			CurrentLevelIndex = MyFirstGameInstance->CurrentLevelIndex;
		}
	}

	// Init for a level
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	for (int32 i = 0; i < ItemToSpawn; i++ )

		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				// Randomly Spawn Item to Level
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				// Count spawned coins. Only count a type of Coin.
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}


	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMySecondGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);


}

void AMySecondGameState::OnLevelTimeUp()
{
	OnGameOver();
}

void AMySecondGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UpdateHUD();
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount)

		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
		{
			EndLevel();
		}
}

void AMySecondGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	UpdateHUD();

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyFirstGameInstance* MyFirstGameInstance = Cast<UMyFirstGameInstance>(GameInstance);
		if (MyFirstGameInstance)
		{
			AddScore(Score);
			CurrentLevelIndex++;
			// Update the Value of Level Index
			MyFirstGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}

	else
	{
		OnGameOver();
	}
}

void AMySecondGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyFirstPlayerController* MyPlayerController = Cast<AMyFirstPlayerController>(PlayerController))
		{
			MyPlayerController->ShowMainMenu(true);
			MyPlayerController->SetPause(true);
		}
	}
}



void AMySecondGameState::HUDValidCheck()
{

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyFirstPlayerController* MyFirstPlayerController = Cast<AMyFirstPlayerController>(PlayerController))
		{
			if (UUserWidget* FoundHUDWidget = MyFirstPlayerController->GetHUDWidget())
			{
				HUDWidget = FoundHUDWidget;
				isHUDValid = true;
				UpdateHUD();
			}
		}
	}
	
}

void AMySecondGameState::UpdateHUD()
{
	if (isHUDValid)
	{
		if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("ScoreValue"))))
		{
			if (UGameInstance* GameInstance = GetGameInstance())
			{
				UMyFirstGameInstance* MyFirstGameInstance = Cast<UMyFirstGameInstance>(GameInstance);
				if (MyFirstGameInstance)
				{
					ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), MyFirstGameInstance->TotalScore)));
				}
			}
		}

		if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("CurrentLevel"))))
		{
			LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex+1)));
		}
	}
}
void AMySecondGameState::UpdateHUDTime()
{
	if (isHUDValid && HUDWidget)
	{
		UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("RemainingTime")));
		if (TimeText)
		{
			float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
			TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
		}
	}
}