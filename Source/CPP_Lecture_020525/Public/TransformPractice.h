// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/StaticMeshComponent.h"
//#include "Engine/Engine.h"
#include "TransformPractice.generated.h"

UCLASS()
class CPP_LECTURE_020525_API ATransformPractice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransformPractice();
	UFUNCTION(BlueprintCallable, Category = "Practice|PrintToScreen")
	void PrintToScreen(const FString& Message, FColor Color = FColor::Black, float Duration = 2.0f);
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Prctice|SceneRoot")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Prctice|StaticMeshComp")
	UStaticMeshComponent* StaticMeshComp;
	//FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Prctice|RotationSpeedAdjustment")
	float RotationSpeed;
	//Booster to increase the DeltaTime.
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Prctice|Booster", meta = (ClampMin = "0.1", ClampMax = "5.0"))
	float Booster;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
