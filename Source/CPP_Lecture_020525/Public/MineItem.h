#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class CPP_LECTURE_020525_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AMineItem();

	USphereComponent* ExplosionCollision;

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;
	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item|Effects")
	USoundBase* ExplosionSound;

	FTimerHandle ExplosionTimerHandle;
	
	bool bIsTouched;

	virtual void ActivateItem(AActor* Activator) override;
	void Explode();
};