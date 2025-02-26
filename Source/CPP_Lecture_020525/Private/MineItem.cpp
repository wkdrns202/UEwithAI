#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AMineItem::AMineItem()

{
	ExplosionDelay = 2.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30;
	ItemType = "Mine";

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);
	bIsTouched = false;
}


void AMineItem::ActivateItem(AActor* Activator)
{
	if (bIsTouched) return;


	Super::ActivateItem(Activator);

	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AMineItem::Explode,
		ExplosionDelay,
		false
	);
	// ItemCounts -= 1;
	bIsTouched = true;
	
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::FromInt(ItemCounts));
	
	
}

void AMineItem::Explode()
{
	UParticleSystemComponent* Particle = nullptr;
	if (ExplosionParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			false
		);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound,
			GetActorLocation()
		);
	}

	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			//GEngine->AddOnScreenDebugMessage(-1,
			//	2.0f,
			//	FColor::Green,
			//	FString::Printf(TEXT("Player Damaged about %d"), ExplosionDamage));

			UGameplayStatics::ApplyDamage(
				Actor, ExplosionDamage, nullptr, this, UDamageType::StaticClass()
			);
		}
	}

	DestroyItem();

	if (Particle)
	{
		FTimerHandle DestroyParticleTimerHandle;

		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			[Particle]()
			{// 2초 카운트가 진행되는 사이 레벨이 전환되거나 게임 종료될 경우 에러발생.. 어떻게 예외처리 할 수 있을지?
				Particle->DestroyComponent();
			},
			2.0f,
			false
		);
	}
}