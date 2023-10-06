// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberActor.h"

// Sets default values
ALumberActor::ALumberActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	OnClicked.AddUniqueDynamic(this, &ALumberActor::OnSelected);

}

// Called when the game starts or when spawned
void ALumberActor::BeginPlay()
{
	Super::BeginPlay();
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstanceRef) gameInstanceRef->AdjustLumberProductionAmount(baseLumberProductionAmount);
}

// Called every frame
void ALumberActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALumberActor::OnSelected(AActor* Target, FKey ButtonPressed)
{
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstanceRef) {
		if (gameInstanceRef->GetCurrentConstructMenuState() == ConstructMenuStates::Upgrade) {
			if (currentTierLvl == 1) {
				if (gameInstanceRef->GetWoodAmount() >= tier2WoodUpgradePrice && gameInstanceRef->GetGoldAmount() >= tier2GoldUpgradePrice) {
					gameInstanceRef->SpendWood(tier2WoodUpgradePrice);
					gameInstanceRef->SpendGold(tier2GoldUpgradePrice);
					currentTierLvl = 2;
					if (gameInstanceRef) gameInstanceRef->AdjustLumberProductionAmount(tier2LumberProductionAmount);
				}
			}
			else if (currentTierLvl == 2) {
				if (gameInstanceRef->GetWoodAmount() >= tier3WoodUpgradePrice && gameInstanceRef->GetGoldAmount() >= tier3GoldUpgradePrice) {
					gameInstanceRef->SpendWood(tier3WoodUpgradePrice);
					gameInstanceRef->SpendGold(tier3GoldUpgradePrice);
					currentTierLvl = 3;
					if (gameInstanceRef) gameInstanceRef->AdjustLumberProductionAmount(tier3LumberProductionAmount);
				}
			}
		}
		else if (gameInstanceRef->GetCurrentConstructMenuState() == ConstructMenuStates::Bulldoze) {
			if (currentTierLvl == 1) {
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				gameInstanceRef->AddGoldAmount(baseLumberSellPrice);
				if (gameInstanceRef) gameInstanceRef->AdjustLumberProductionAmount(-baseLumberProductionAmount);
				Destroy();
			}
			else if (currentTierLvl == 2) {
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				gameInstanceRef->AddGoldAmount(tier2LumberSellPrice);
				if (gameInstanceRef) gameInstanceRef->AdjustLumberProductionAmount(-tier2LumberProductionAmount);
				Destroy();
			}
			else if (currentTierLvl == 3) {
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				gameInstanceRef->AddGoldAmount(tier3LumberSellPrice);
				if (gameInstanceRef) gameInstanceRef->AdjustLumberProductionAmount(-tier3LumberProductionAmount);
				Destroy();
			}
		}
	}
}

UFUNCTION() void ALumberActor::StoreBuildingPlacementActor(ABuildingPlacementActor* ref)
{
	originalActor = ref;
	originalActor->SetActorHiddenInGame(true);
}

