// Fill out your copyright notice in the Description page of Project Settings.


#include "MineActor.h"

// Sets default values
AMineActor::AMineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	OnClicked.AddUniqueDynamic(this, &AMineActor::OnSelected);

}

// Called when the game starts or when spawned
void AMineActor::BeginPlay()
{
	Super::BeginPlay();
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstanceRef) gameInstanceRef->AdjustMineProductionAmount(baseMineProductionAmount);
}

// Called every frame
void AMineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMineActor::OnSelected(AActor* Target, FKey ButtonPressed)
{
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstanceRef) {
		if (gameInstanceRef->GetCurrentConstructMenuState() == ConstructMenuStates::Upgrade) {
			if (currentTierLvl == 1) {
				if (gameInstanceRef->GetIronAmount() >= tier2IronUpgradePrice && gameInstanceRef->GetGoldAmount() >= tier2GoldUpgradePrice) {
					gameInstanceRef->SpendIron(tier2IronUpgradePrice);
					gameInstanceRef->SpendGold(tier2GoldUpgradePrice);
					currentTierLvl = 2;
					if (gameInstanceRef) gameInstanceRef->AdjustMineProductionAmount(tier2MineProductionAmount);
				}
			}
			else if (currentTierLvl == 2) {
				if (gameInstanceRef->GetIronAmount() >= tier3IronUpgradePrice && gameInstanceRef->GetGoldAmount() >= tier3GoldUpgradePrice) {
					gameInstanceRef->SpendWood(tier3IronUpgradePrice);
					gameInstanceRef->SpendGold(tier3GoldUpgradePrice);
					currentTierLvl = 3;
					if (gameInstanceRef) gameInstanceRef->AdjustMineProductionAmount(tier3MineProductionAmount);
				}
			}
		}
		else if (gameInstanceRef->GetCurrentConstructMenuState() == ConstructMenuStates::Bulldoze) {
			if (currentTierLvl == 1) {
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				gameInstanceRef->AddGoldAmount(baseMineSellPrice);
				if (gameInstanceRef) gameInstanceRef->AdjustMineProductionAmount(-baseMineProductionAmount);
				Destroy();
			}
			else if (currentTierLvl == 2) {
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				gameInstanceRef->AddGoldAmount(tier2MineSellPrice);
				if (gameInstanceRef) gameInstanceRef->AdjustMineProductionAmount(-tier2MineProductionAmount);
				Destroy();
			}
			else if (currentTierLvl == 3) {
				if (originalActor) originalActor->SetActorHiddenInGame(false);
				gameInstanceRef->AddGoldAmount(tier3MineSellPrice);
				if (gameInstanceRef) gameInstanceRef->AdjustMineProductionAmount(-tier3MineProductionAmount);
				Destroy();
			}
		}
	}
}

UFUNCTION() void AMineActor::StoreBuildingPlacementActor(ABuildingPlacementActor* ref)
{
	originalActor = ref;
	originalActor->SetActorHiddenInGame(true);
}

