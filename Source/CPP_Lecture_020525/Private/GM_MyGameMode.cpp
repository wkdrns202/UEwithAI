// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MyGameMode.h"
#include "MyFirstCharacter.h"
#include "MyFirstPlayerController.h"
#include "MySecondGameState.h"

AGM_MyGameMode::AGM_MyGameMode()
{
	DefaultPawnClass = AMyFirstCharacter::StaticClass();
	PlayerControllerClass = AMyFirstPlayerController::StaticClass();
	GameStateClass = AMySecondGameState::StaticClass();
}
