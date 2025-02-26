// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"

DEFINE_LOG_CATEGORY(LogSoftStory);

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	//'/Game/StarterContent/Props/SM_Chair.SM_Chair'
	//'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'




	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Props/SM_Chair.SM_Chair"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded()) 
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	UE_LOG(LogSoftStory, Warning, TEXT("%s #0 Start"), *GetName());
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogSoftStory, Error, TEXT("%s #1 Post Actor Construction"), *GetName());
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
	/*UE_LOG(LogTemp, Warning, TEXT("My Log!"));
	UE_LOG(LogSoftStory, Error, TEXT("My Soft Story!!"))*/

	UE_LOG(LogSoftStory, Error, TEXT("%s #2 Begin Play"), *GetName());
	
	PrimaryActorTick.bCanEverTick = true;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AItem::DisableTick,  // ✅ Use a function instead of lambda
		3.0f,
		false
	);

	//ItemCounts = 0;
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogSoftStory, Error, TEXT("%s #3 Ticking"), *GetName());
}

void AItem::Destroyed()
{
	UE_LOG(LogSoftStory, Error, TEXT("%s #4 Destroyed"), *GetName());
	Super::Destroyed();
}

void AItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogSoftStory, Error, TEXT("%s #5 EndPlayReason"), *GetName());
	Super::EndPlay(EndPlayReason);
}

void AItem::DisableTick()
{
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogSoftStory, Warning, TEXT("%s #Tick Disabled"), *GetName());
	Destroy();  // ✅ Correct way to remove the actor
}