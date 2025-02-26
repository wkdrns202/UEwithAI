#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "BitCoinItem.generated.h"

UCLASS()
class CPP_LECTURE_020525_API ABitCoinItem : public ACoinItem
{
	GENERATED_BODY()



public:
	ABitCoinItem();

	virtual void ActivateItem(AActor* Activator) override;
	
};
