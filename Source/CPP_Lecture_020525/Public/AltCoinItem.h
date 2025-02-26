#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "AltCoinItem.generated.h"

UCLASS()
class CPP_LECTURE_020525_API AAltCoinItem : public ACoinItem
{
	GENERATED_BODY()
	

	AAltCoinItem();

	virtual void ActivateItem(AActor* Activator) override;

};
