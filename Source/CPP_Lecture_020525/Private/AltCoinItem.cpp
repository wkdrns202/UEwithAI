// Fill out your copyright notice in the Description page of Project Settings.


#include "AltCoinItem.h"

AAltCoinItem::AAltCoinItem()

{
	PointValue = 10;
	ItemType = "AltCoin";

}


void AAltCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}