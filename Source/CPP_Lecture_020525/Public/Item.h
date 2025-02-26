// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "MyFirstCharacter.h"
#include "Item.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSoftStory, Warning, All);

UCLASS()
class CPP_LECTURE_020525_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;
	FTimerHandle TimerHandle;  // ✅ Store timer reference

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float Deltatime) override;
	virtual void Destroyed() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void DisableTick();  // ✅ Function to disable ticking and destroy the actor
};