// Fill out your copyright notice in the Description page of Project Settings.


#include "TransformPractice.h"

// Sets default values
ATransformPractice::ATransformPractice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
	Booster = 1.0f;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Props/SM_Statue.SM_Statue"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}*/
	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset1(TEXT("/Game/StarterContent/Props/Materials/M_StatueGlass.M_StatueGlass"));
	if (MaterialAsset1.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset1.Object);
	}	
	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset2(TEXT("/Game/StarterContent/Props/Materials/M_Statue.M_Statue"));
	if (MaterialAsset2.Succeeded())
	{
		StaticMeshComp->SetMaterial(1, MaterialAsset2.Object);
	}
}

void ATransformPractice::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Detail 패널에서 설정된 Static Mesh가 없을 경우 기본 메시 설정
	if (StaticMeshComp && StaticMeshComp->GetStaticMesh() == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Props/SM_Statue.SM_Statue"));
		if (MeshAsset.Succeeded())
		{
			StaticMeshComp->SetStaticMesh(MeshAsset.Object);
		}
	}
}

// Called when the game starts or when spawned
void ATransformPractice::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(140.0f, 0.0f, 10.0f));
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	// pitch, yaw, roll (Y,Z,X)
	SetActorScale3D(FVector(1.0f));
	
}

// Called every frame
void ATransformPractice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorWorldRotation(FRotator(0.0f, RotationSpeed * (DeltaTime/2), 0.0f));
	}

	// Time accumulator
	static float TimeElapsed = 0.0f;
	
	TimeElapsed += DeltaTime * Booster;

	// Scale oscillation using Sin wave
	float ScaleFactor = 1.0f + 0.5f * FMath::Sin(TimeElapsed * PI); // Oscillates between 0.5x to 1.5x scale

	SetActorScale3D(FVector(ScaleFactor));


	//PrintToScreen("Tick Function Enable", FColor::Green, 0.000005f);
}

void ATransformPractice::PrintToScreen(const FString& Message, FColor Color, float Duration)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
}
