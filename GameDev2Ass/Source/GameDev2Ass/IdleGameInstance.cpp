// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleGameInstance.h"
#include "BuildingPlacementActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "FarmActor.h"
#include "LumberActor.h"
#include "MineActor.h"

UIdleGameInstance::UIdleGameInstance(const FObjectInitializer& ObjectInitializer) {

	UE_LOG(LogTemp, Warning, TEXT("GameInstanceConstructor"));

}

void UIdleGameInstance::Init()
{
	Super::Init();

}

void UIdleGameInstance::Shutdown()
{
	Super::Shutdown();
}

UFUNCTION()ConstructMenuStates UIdleGameInstance::GetCurrentConstructMenuState()
{
	return ConstructMenuState;
}

UFUNCTION() void UIdleGameInstance::SelectConstructMenuState(ConstructMenuStates type)
{
	ConstructMenuState = type;
}

UFUNCTION()StructureTypes UIdleGameInstance::GetCurrentStructureType()
{
	return StructureType;
}

UFUNCTION() void UIdleGameInstance::SelectCurrentStructureType(StructureTypes type)
{
	StructureType = type;
}

UFUNCTION() void UIdleGameInstance::SelectBuildableSpace(ABuildingPlacementActor* selected)
{
	if(currentSelected) currentSelected->Unselect();
	currentSelected = selected;
}

UFUNCTION() bool UIdleGameInstance::bCheckFarmBuildability()
{
	if (baseFarmFoodPrice <= foodAmount && baseFarmGoldPrice <= goldAmount && baseFarmWoodPrice <= woodAmount) {
		return true;
	}
	else return false;
}

UFUNCTION() void UIdleGameInstance::FarmBuildTransaction()
{
	if (FarmActorClass) {
		foodAmount -= baseFarmFoodPrice;
		goldAmount -= baseFarmGoldPrice;
		woodAmount -= baseFarmWoodPrice;
		AFarmActor* TempTower = GetWorld()->SpawnActor<AFarmActor>(FarmActorClass, currentSelected->GetActorLocation(), currentSelected->GetActorRotation());
		if (TempTower)TempTower->StoreBuildingPlacementActor(currentSelected);
	}
}

UFUNCTION() bool UIdleGameInstance::bCheckLumberBuildability()
{
	if (baseLumberIronPrice <= ironAmount && baseLumberGoldPrice <= goldAmount && baseLumberWoodPrice <= woodAmount) {
		return true;
	}
	else return false;
}

UFUNCTION() void UIdleGameInstance::LumberBuildTransaction()
{
	ironAmount -= baseLumberIronPrice;
	goldAmount -= baseLumberGoldPrice;
	woodAmount -= baseLumberWoodPrice;
	ALumberActor* TempTower = GetWorld()->SpawnActor<ALumberActor>(LumberActorClass, currentSelected->GetActorLocation(), currentSelected->GetActorRotation());
	if (TempTower)TempTower->StoreBuildingPlacementActor(currentSelected);
}

UFUNCTION() bool UIdleGameInstance::bCheckMineBuildability()
{
	if (baseMineIronPrice <= ironAmount && baseMineGoldPrice <= goldAmount && baseMineWoodPrice <= woodAmount) {
		return true;
	}
	else return false;
}

UFUNCTION() void UIdleGameInstance::MineBuildTransaction()
{
	ironAmount -= baseMineIronPrice;
	goldAmount -= baseMineGoldPrice;
	woodAmount -= baseMineWoodPrice;
	AMineActor* TempTower = GetWorld()->SpawnActor<AMineActor>(MineActorClass, currentSelected->GetActorLocation(), currentSelected->GetActorRotation());
	if (TempTower)TempTower->StoreBuildingPlacementActor(currentSelected);
}

UFUNCTION() void UIdleGameInstance::AdjustFarmProductionAmount(int adjustment)
{
	farmProductionAmount += adjustment;
}

UFUNCTION() void UIdleGameInstance::AdjustLumberProductionAmount(int adjustment)
{
	lumberProductionAmount += adjustment;
}

UFUNCTION() void UIdleGameInstance::AdjustMineProductionAmount(int adjustment)
{
	mineProductionAmount+= adjustment;
}

int UIdleGameInstance::GetFoodAmount()
{
	return foodAmount;
}

void UIdleGameInstance::AddFoodAmount(int amount)
{
	foodAmount += amount;
}

UFUNCTION() void UIdleGameInstance::SpendFood(int amount)
{
	if (foodAmount >= amount) foodAmount -= amount;
}

int UIdleGameInstance::GetGoldAmount()
{
	return goldAmount;
}

void UIdleGameInstance::AddGoldAmount(int amount)
{
	goldAmount += amount;
}

UFUNCTION() void UIdleGameInstance::SpendGold(int amount)
{
	if (goldAmount >= amount) goldAmount -= amount;
}

int UIdleGameInstance::GetIronAmount()
{
	return ironAmount;
}

void UIdleGameInstance::AddIronAmount(int amount)
{
	ironAmount += amount;
}

UFUNCTION() void UIdleGameInstance::SpendIron(int amount)
{
	if (ironAmount >= amount) ironAmount -= amount;
}

int UIdleGameInstance::GetWoodAmount()
{
	return woodAmount;
}

void UIdleGameInstance::AddWoodAmount(int amount)
{
	woodAmount += amount;
}

UFUNCTION() void UIdleGameInstance::SpendWood(int amount)
{
	if (woodAmount >= amount) woodAmount -= amount;
}

UFUNCTION() void UIdleGameInstance::TimeTick(float frameTime)
{
	timeStorage += frameTime;
	foodTimer = fmod(timeStorage, (baseResourceRate - farmPop));
	woodTimer = fmod(timeStorage, (baseResourceRate - lumberPop));
	ironTimer = fmod(timeStorage, (baseResourceRate - minePop));
	goldDrainTimer = fmod(timeStorage, goldDrainDelay);
	shopRefreshTimer = fmod(timeStorage, shopRefreshDelay);
	if (foodTimer < previousFoodTimer) foodAmount += farmProductionAmount;
	if (woodTimer < previousWoodTimer) woodAmount += lumberProductionAmount;
	if (ironTimer < previousIronTimer) ironAmount += mineProductionAmount;
	if (goldDrainTimer < previousGoldDrainTimer && goldAmount > 0) goldAmount--;
	if (shopRefreshTimer < previousShopRefreshTimer) {
		shopFoodAmount += shopFoodRefreshAmount;
		if (shopFoodAmount > shopFoodLimit) shopFoodAmount = shopFoodLimit;
		shopIronAmount += shopIronRefreshAmount;
		if (shopIronAmount > shopIronLimit) shopIronAmount = shopIronLimit;
		shopGoldAmount += shopGoldRefreshAmount;
		if (shopGoldAmount > shopGoldLimit) shopGoldAmount = shopGoldLimit;
		shopWoodAmount += shopWoodRefreshAmount;
		if (shopWoodAmount > shopWoodLimit) shopWoodAmount = shopWoodLimit;
	}
	previousFoodTimer = foodTimer;
	previousGoldDrainTimer = goldDrainTimer;
	previousIronTimer = ironTimer;
	previousShopRefreshTimer = shopRefreshTimer;
	previousWoodTimer = woodTimer;
}

int UIdleGameInstance::GetPopulationAmount()
{
	return populationAmount;
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::IncreasePopulationAmount()
{
	if (foodAmount > villagerFoodCost) {
		foodAmount -= villagerFoodCost;
		populationAmount++;
		sparePopulationAmount++;
		villagerFoodCost += populationAmount / 2;
	}
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetVillagerFoodCost()
{
	return villagerFoodCost;
}

int UIdleGameInstance::GetSparePopulationAmount()
{
	return sparePopulationAmount;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetShopFoodAmount()
{
	return shopFoodAmount;
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::BuyFood()
{
	if (goldAmount >= shopFoodBuyPrice && shopFoodAmount > 0) {
		shopGoldAmount += shopFoodBuyPrice;
		goldAmount -= shopFoodBuyPrice;
		foodAmount++;
		shopFoodAmount--;
	}
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::SellFood()
{
	if (shopGoldAmount >= shopFoodSellPrice && foodAmount > 0) {
		shopGoldAmount -= shopFoodSellPrice;
		goldAmount += shopFoodSellPrice;
		foodAmount--;
		shopFoodAmount++;
	}
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetShopIronAmount()
{
	return shopIronAmount;
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::BuyIron()
{
	if (goldAmount >= shopIronBuyPrice && shopIronAmount > 0) {
		shopGoldAmount += shopIronBuyPrice;
		goldAmount -= shopIronBuyPrice;
		ironAmount++;
		shopIronAmount--;
	}
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::SellIron()
{
	if (shopGoldAmount >= shopIronSellPrice && ironAmount > 0) {
		shopGoldAmount -= shopIronSellPrice;
		goldAmount += shopIronSellPrice;
		ironAmount--;
		shopIronAmount++;
	}
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetShopWoodAmount()
{
	return shopWoodAmount;
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::BuyWood()
{
	if (goldAmount >= shopWoodBuyPrice && shopWoodAmount > 0) {
		shopGoldAmount += shopWoodBuyPrice;
		goldAmount -= shopWoodBuyPrice;
		woodAmount++;
		shopWoodAmount--;
	}
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::SellWood()
{
	if (shopGoldAmount >= shopWoodSellPrice && woodAmount > 0) {
		shopGoldAmount -= shopWoodSellPrice;
		goldAmount += shopWoodSellPrice;
		woodAmount--;
		shopWoodAmount++;
	}
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetShopGoldAmount()
{
	return shopGoldAmount;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseFarmWoodPrice()
{
	return baseFarmWoodPrice;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseFarmFoodPrice()
{
	return baseFarmFoodPrice;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseFarmGoldPrice()
{
	return baseFarmGoldPrice;
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::IncreaseFarmPopAmount()
{
	if (sparePopulationAmount > 0 && farmPop < farmPopAllowance) {
		sparePopulationAmount--;
		farmPop++;
	}
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::DecreaseFarmPopAmount()
{
	if (farmPop > 0) {
		sparePopulationAmount++;
		farmPop--;
	}
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetFarmPopAmount()
{
	return farmPop;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetFarmPopAllowanceAmount()
{
	return farmPopAllowance;
}

UFUNCTION() void UIdleGameInstance::RecalculateFarmPopAllowance()
{
	return UFUNCTION() void();
}

UFUNCTION() bool UIdleGameInstance::bConstructFarmActor()
{
	return UFUNCTION() bool();
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseLumberWoodPrice()
{
	return baseLumberWoodPrice;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseLumberIronPrice()
{
	return baseLumberIronPrice;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseLumberGoldPrice()
{
	return baseLumberGoldPrice;
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::IncreaseLumberPopAmount()
{
	if (sparePopulationAmount > 0 && lumberPop < lumberPopAllowance) {
		sparePopulationAmount--;
		lumberPop++;
	}
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::DecreaseLumberPopAmount()
{
	if (lumberPop > 0) {
		sparePopulationAmount++;
		lumberPop--;
	}
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetLumberPopAmount()
{
	return lumberPop;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetLumberPopAllowanceAmount()
{
	return lumberPopAllowance;
}

UFUNCTION() void UIdleGameInstance::RecalculateLumberPopAllowance()
{
	return UFUNCTION() void();
}

UFUNCTION() bool UIdleGameInstance::bConstructLumberActor()
{
	return UFUNCTION() bool();
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseMineWoodPrice()
{
	return baseMineWoodPrice;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseMineIronPrice()
{
	return baseMineIronPrice;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetBaseMineGoldPrice()
{
	return baseMineGoldPrice;
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::IncreaseMinePopAmount()
{
	if (sparePopulationAmount > 0 && minePop < minePopAllowance) {
		sparePopulationAmount--;
		minePop++;
	}
}

UFUNCTION(BlueprintCallable) void UIdleGameInstance::DecreaseMinePopAmount()
{
	if (minePop > 0) {
		sparePopulationAmount++;
		minePop--;
	}
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetMinePopAmount()
{
	return minePop;
}

UFUNCTION(BlueprintCallable) int UIdleGameInstance::GetMinePopAllowanceAmount()
{
	return minePopAllowance;
}

UFUNCTION() void UIdleGameInstance::RecalculateMinePopAllowance()
{
	return UFUNCTION() void();
}

UFUNCTION() bool UIdleGameInstance::bConstructMineActor()
{
	return UFUNCTION() bool();
}
