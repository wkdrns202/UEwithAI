// Fill out your copyright notice in the Description page of Project Settings.


#include "BitCoinItem.h"

ABitCoinItem::ABitCoinItem()

{
	PointValue = 50;
	ItemType = "BitCoin";

}


void ABitCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}