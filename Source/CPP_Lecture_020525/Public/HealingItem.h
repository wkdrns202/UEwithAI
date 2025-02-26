#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"

UCLASS()
class CPP_LECTURE_020525_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()
	

public:
	AHealingItem();

	UPROPERTY(EditANywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;


};
