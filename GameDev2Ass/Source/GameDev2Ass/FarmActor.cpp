// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmActor.h"

// Sets default values
AFarmActor::AFarmActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	OnClicked.AddUniqueDynamic(this, &AFarmActor::OnSelected);

}

// Called when the game starts or when spawned
void AFarmActor::BeginPlay()
{
	Super::BeginPlay();
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstanceRef) gameInstanceRef->AdjustFarmProductionAmount(baseFoodProductionAmount);
}

// Called every frame
void AFarmActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFarmActor::OnSelected(AActor* Target, FKey ButtonPressed)
{
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstanceRef) {
		if (gameInstanceRef->GetCurrentConstructMenuState() == ConstructMenuStates::Upgrade) {
			if (currentTierLvl == 1) {
				if (gameInstanceRef->GetWoodAmount() >= tier2WoodUpgradePrice && gameInstanceRef->GetGoldAmount() >= tier2GoldUpgradePrice) {
					gameInstanceRef->SpendWood(tier2WoodUpgradePrice);
					gameInstanceRef->SpendGold(tier2GoldUpgradePrice);
					currentTierLvl = 2;
					if (gameInstanceRef) gameInstanceRef->AdjustFarmProductionAmount(tier2FoodProductionAmount);

				}
			}
			else if (currentTierLvl == 2) {
				if (gameInstanceRef->GetWoodAmount() >= tier3WoodUpgradePrice && gameInstanceRef->GetGoldAmount() >= tier3GoldUpgradePrice) {
					gameInstanceRef->SpendWood(tier3WoodUpgradePrice);
					gameInstanceRef->SpendGold(tier3GoldUpgradePrice);
					currentTierLvl = 3;
					if (gameInstanceRef) gameInstanceRef->AdjustFarmProductionAmount(tier3FoodProductionAmount);

				}
			}
		}
		else if (gameInstanceRef->GetCurrentConstructMenuState() == ConstructMenuStates::Bulldoze) {
			if (currentTierLvl == 1) {
				gameInstanceRef->AddGoldAmount(baseFoodSellPrice);
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				if (gameInstanceRef) gameInstanceRef->AdjustFarmProductionAmount(-baseFoodProductionAmount);

				Destroy();
			}
			else if (currentTierLvl == 2) {
				gameInstanceRef->AddGoldAmount(tier2FoodSellPrice);
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				if (gameInstanceRef) gameInstanceRef->AdjustFarmProductionAmount(-tier2FoodProductionAmount);

				Destroy();
			}
			else if (currentTierLvl == 3) {
				gameInstanceRef->AddGoldAmount(tier3FoodSellPrice);
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				if (gameInstanceRef) gameInstanceRef->AdjustFarmProductionAmount(-tier3FoodProductionAmount);

				Destroy();
			}
		}
	}
}

UFUNCTION() void AFarmActor::StoreBuildingPlacementActor(ABuildingPlacementActor* ref)
{
	originalActor = ref;
	originalActor->SetActorHiddenInGame(true);
}

