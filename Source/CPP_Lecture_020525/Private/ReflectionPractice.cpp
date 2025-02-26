// Fill out your copyright notice in the Description page of Project Settings.


#include "ReflectionPractice.h"

// Sets default values
AReflectionPractice::AReflectionPractice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 0.0f;
}

// Called when the game starts or when spawned
void AReflectionPractice::BeginPlay()
{
	Super::BeginPlay();
	OnItemPickedUP();
}

// Called every frame
void AReflectionPractice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReflectionPractice::ResetActorPosition()
{
	SetActorLocation(FVector::ZeroVector);
}

float AReflectionPractice::GetRotationSpeed() const
{
	return RotationSpeed;
}