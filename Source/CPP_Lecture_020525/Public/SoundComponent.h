// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "SoundComponent.generated.h"



UCLASS()
class CPP_LECTURE_020525_API ASoundComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundComponent();
	virtual void BeginPlay() override;

	void PrintToScreen(const FString& Message, FColor Color = FColor::Black, float Duration = 2.0f);
	

protected:
	USceneComponent* SceneRoot;
	UAudioComponent* Audio;
	
};
