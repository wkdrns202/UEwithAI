// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundComponent.h"

// Sets default values
ASoundComponent::ASoundComponent()
{

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	Audio->SetupAttachment(SceneRoot);

	
	static ConstructorHelpers::FObjectFinder<USoundCue>SoundCueAsset(TEXT("/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue"));
	if (SoundCueAsset.Succeeded())
	{
		Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
		Audio->SetupAttachment(SceneRoot);
		Audio->SetSound(SoundCueAsset.Object);
		Audio->bAutoActivate = false;
		Audio->PitchMultiplier = 0.8f;
	}
}

void ASoundComponent::BeginPlay()
{
	Super::BeginPlay();

	PrintToScreen(TEXT("Hello from C++!"), FColor::White, 5.0f);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this]() {
			Audio->Play();
		},
		1.5f,
		false
	);
}

void ASoundComponent::PrintToScreen(const FString& Message, FColor Color, float Duration)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
}
