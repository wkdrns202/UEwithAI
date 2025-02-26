#include "CoinItem.h"
#include "Engine/World.h"
#include "MySecondGameState.h"

ACoinItem::ACoinItem() 
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (AMySecondGameState* GameState = World->GetGameState<AMySecondGameState>()) 
			{
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();

				GEngine->AddOnScreenDebugMessage(
					-1,
					2.0f,
					FColor::Green,
					FString::Printf(TEXT("Player Earned %d Points"), PointValue));

				//ItemCounts -= 1;

				/*GEngine->AddOnScreenDebugMessage(
					-1, 
					2.0f, 
					FColor::Blue, 
					FString::FromInt(ItemCounts));*/

			}
		}


		DestroyItem();
	}
}