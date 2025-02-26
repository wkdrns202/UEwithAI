#include "MyFirstPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "MyFirstGameInstance.h"
#include "MySecondGameState.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MySecondGameState.h"
#include "Components/TextBlock.h"

AMyFirstPlayerController::AMyFirstPlayerController()
	: InputMappingContext(nullptr),
	MoveActionCool(nullptr),
	JumpActionYes(nullptr),
	LookUpActionBravo(nullptr),
	TurnActionBravo(nullptr),
	SprintActionNice(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
}

void AMyFirstPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (InputMappingContext)
				{
					Subsystem->AddMappingContext(InputMappingContext, 0);
				}
			}

	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}

UUserWidget* AMyFirstPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void AMyFirstPlayerController::ShowMainMenu(bool bIsRestart)
{
	
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (!MainMenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("####MainMenuWidgetClass is false"));
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);

		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true; // 마우스 커서가 보이도록.
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
				bRestartOnCurrentLevel = true;
			}

			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}

			
		}

		if (bIsRestart)
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}
			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				if (UMyFirstGameInstance* GameInstance = Cast<UMyFirstGameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Total Score: %d"), GameInstance->TotalScore)
					));
				}
			}
		}
	}
}

void AMyFirstPlayerController::ShowGameHUD()
{
	// 점수, 레벨, 남은시간 등을 보여주는 HUD 작동중이면 제거.
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	// MainMenu 떠있는 경우도 제거.
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}


	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
			bShowMouseCursor = false; // 마우스 커서가 보이지 않도록.
			SetInputMode(FInputModeGameOnly());
		}

		// GetWorld()의 return값이 True면 해당월드의 AMySecondGameState 호출. False면 nullptr 반환.
		AMySecondGameState* GameState = GetWorld() ? GetWorld()->GetGameState<AMySecondGameState>() : nullptr;

		if (GameState)
		{
			GameState->UpdateHUD();
		}
	}
}

void AMyFirstPlayerController::StartGame()
{
	UMyFirstGameInstance* MyFirstGameInstance = Cast<UMyFirstGameInstance>(UGameplayStatics::GetGameInstance(this));
	AMySecondGameState* GameStateForLevelIndex = Cast<AMySecondGameState>(GetWorld()->GetGameState<AMySecondGameState>());
	SetPause(false);
		
	// 첫 시작일 때 0번 인덱스에서 실행되도록 CurrentLevelIndex 세팅
	if (!bRestartOnCurrentLevel)
	{
		if (MyFirstGameInstance)
		{
			MyFirstGameInstance->CurrentLevelIndex = 0;
			MyFirstGameInstance->TotalScore = 0;
		}
	}
	// 첫 시작이 아닐 때, 해당 레벨에서 실행되도록 Instance에 저장되어있는 최신 CurrentLevelIndex 참조하게끔 세팅
	if (MyFirstGameInstance)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(GameStateForLevelIndex->LevelMapNames[MyFirstGameInstance->CurrentLevelIndex]));
		int CurrentLevelCheck = MyFirstGameInstance->CurrentLevelIndex;
		UE_LOG(LogTemp, Error, TEXT("The Current Level Number is %d"), CurrentLevelCheck+1);
	}
	
	
}

