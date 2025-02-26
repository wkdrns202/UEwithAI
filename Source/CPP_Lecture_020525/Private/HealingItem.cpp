// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "MyFirstCharacter.h"

AHealingItem::AHealingItem()

{
	HealAmount = 20;
	ItemType = "Healing";

}


void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	//GEngine->AddOnScreenDebugMessage(-1,
	//	2.0f,
	//	FColor::Green,
	//	FString::Printf(TEXT("Player Earned %d Health Points"), HealAmount));
	//ItemCounts -= 1;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::FromInt(ItemCounts));

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AMyFirstCharacter* PlayerCharacter = Cast<AMyFirstCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}


		DestroyItem();
	}	
}