// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Math/UnrealMathUtility.h"
#include "IdleGameInstance.generated.h"

class ABuildingPlacementActor;
class AFarmActor;
class ALumberActor;
class AMineActor;
class ATurretActor;

UENUM()
enum class ConstructMenuStates : uint8 {
	Build					 UMETA(DisplayName = "Build"),
	Bulldoze				 UMETA(DisplayName = "Bulldoze"),
	Upgrade					 UMETA(DisplayName = "Upgrade"),
	Error					 UMETA(DisplayName = "Error"),
};

UENUM()
enum class StructureTypes : uint8 {
	Farm					 UMETA(DisplayName = "Farm"),
	Lumber					 UMETA(DisplayName = "Lumber"),
	Mine					 UMETA(DisplayName = "Mine"),
	Tower					 UMETA(DisplayName = "Tower"),
	Error					 UMETA(DisplayName = "Error"),
};

/**
 * 
 */
UCLASS()
class GAMEDEV2ASS_API UIdleGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UIdleGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;
	virtual void Shutdown() override;

	//Enum set up
	UFUNCTION() ConstructMenuStates GetCurrentConstructMenuState();
	UFUNCTION() void SelectConstructMenuState(ConstructMenuStates type);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status) TEnumAsByte<ConstructMenuStates> ConstructMenuState = ConstructMenuStates::Error;
	UFUNCTION() StructureTypes GetCurrentStructureType();
	UFUNCTION() void SelectCurrentStructureType(StructureTypes type);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status) TEnumAsByte<StructureTypes> StructureType = StructureTypes::Error;

	//SelectionOfObjects
	UFUNCTION() void SelectBuildableSpace(ABuildingPlacementActor* selected);
	UPROPERTY() ABuildingPlacementActor* currentSelected;
	UFUNCTION() bool bCheckFarmBuildability();
	UFUNCTION() void FarmBuildTransaction();
	UFUNCTION() bool bCheckLumberBuildability();
	UFUNCTION() void LumberBuildTransaction();	
	UFUNCTION() bool bCheckMineBuildability();
	UFUNCTION() void MineBuildTransaction();
	UFUNCTION() void AdjustFarmProductionAmount(int adjustment);
	UFUNCTION() void AdjustLumberProductionAmount(int adjustment);
	UFUNCTION() void AdjustMineProductionAmount(int adjustment);

	//ResourceFunctionality
	UFUNCTION(BlueprintCallable) int GetFoodAmount();
	UFUNCTION() void AddFoodAmount(int amount);
	UFUNCTION() void SpendFood(int amount);

	UFUNCTION(BlueprintCallable) int GetGoldAmount();
	UFUNCTION() void AddGoldAmount(int amount);
	UFUNCTION() void SpendGold(int amount);

	UFUNCTION(BlueprintCallable) int GetIronAmount();
	UFUNCTION() void AddIronAmount(int amount);
	UFUNCTION() void SpendIron(int amount);

	UFUNCTION(BlueprintCallable) int GetWoodAmount();
	UFUNCTION() void AddWoodAmount(int amount);
	UFUNCTION() void SpendWood(int amount);

	UFUNCTION() void TimeTick(float frameTime);

private:

	//Resource initialisation
	UPROPERTY(EditAnywhere) int startingFoodAmount = 5;
	UPROPERTY() int foodAmount = startingFoodAmount;

	UPROPERTY(EditAnywhere) int startingGoldAmount = 25;
	UPROPERTY() int goldAmount = startingGoldAmount;

	UPROPERTY(EditAnywhere) int startingIronAmount = 5;
	UPROPERTY() int ironAmount = startingIronAmount;

	UPROPERTY(EditAnywhere) int startingWoodAmount = 5;
	UPROPERTY() int woodAmount = startingWoodAmount;

	UPROPERTY(EditAnywhere) int startingPopulationAmount = 5;
	UPROPERTY() int populationAmount = startingPopulationAmount;
	UFUNCTION(BlueprintCallable) int GetPopulationAmount();
	UFUNCTION(BlueprintCallable) void IncreasePopulationAmount();
	UPROPERTY(EditAnywhere) int baseVillagerFoodCost = 5;
	UPROPERTY(EditAnywhere) int villagerFoodCost = baseVillagerFoodCost;
	UFUNCTION(BlueprintCallable) int GetVillagerFoodCost();

	UPROPERTY() int sparePopulationAmount = startingPopulationAmount;
	UFUNCTION(BlueprintCallable) int GetSparePopulationAmount();

	//Shop setup
	UPROPERTY(EditAnywhere) int shopFoodRefreshAmount = 5;
	UPROPERTY(EditAnywhere) int shopFoodLimit = 25;
	UPROPERTY() int shopFoodAmount = 5;
	UPROPERTY(EditAnywhere) int shopFoodBuyPrice = 5;
	UPROPERTY(EditAnywhere) int shopFoodSellPrice = 3;
	UFUNCTION(BlueprintCallable) int GetShopFoodAmount();
	UFUNCTION(BlueprintCallable) void BuyFood();
	UFUNCTION(BlueprintCallable) void SellFood();

	UPROPERTY(EditAnywhere) int shopIronRefreshAmount = 5;
	UPROPERTY(EditAnywhere) int shopIronLimit = 25;
	UPROPERTY() int shopIronAmount = 5;
	UPROPERTY(EditAnywhere) int shopIronBuyPrice = 5;
	UPROPERTY(EditAnywhere) int shopIronSellPrice = 3;
	UFUNCTION(BlueprintCallable) int GetShopIronAmount();
	UFUNCTION(BlueprintCallable) void BuyIron();
	UFUNCTION(BlueprintCallable) void SellIron();

	UPROPERTY(EditAnywhere) int shopWoodRefreshAmount = 5;
	UPROPERTY(EditAnywhere) int shopWoodLimit = 25;
	UPROPERTY() int shopWoodAmount = 5;
	UPROPERTY(EditAnywhere) int shopWoodBuyPrice = 5;
	UPROPERTY(EditAnywhere) int shopWoodSellPrice = 3;
	UFUNCTION(BlueprintCallable) int GetShopWoodAmount();
	UFUNCTION(BlueprintCallable) void BuyWood();
	UFUNCTION(BlueprintCallable) void SellWood();

	UPROPERTY(EditAnywhere) int shopGoldRefreshAmount = 20;
	UPROPERTY(EditAnywhere) int shopGoldLimit = 100;
	UPROPERTY() int shopGoldAmount = 5;
	UFUNCTION(BlueprintCallable) int GetShopGoldAmount();


	//Building Initialisation
	UPROPERTY() float timeStorage = 0.0f;
	UPROPERTY(EditAnywhere) float baseResourceRate = 11.0f;
	UPROPERTY(EditAnywhere) float goldDrainDelay = 60.0f;
	UPROPERTY(EditAnywhere) float shopRefreshDelay = 90.0f;
	UPROPERTY() float foodTimer = 0.0f;
	UPROPERTY() float woodTimer = 0.0f;
	UPROPERTY() float ironTimer = 0.0f;
	UPROPERTY() float goldDrainTimer = 0.0f;
	UPROPERTY() float shopRefreshTimer = 0.0f;

	UPROPERTY() float previousFoodTimer = 1.0f;
	UPROPERTY() float previousWoodTimer = 1.0f;
	UPROPERTY() float previousIronTimer = 1.0f;
	UPROPERTY() float previousGoldDrainTimer = 1.0f;
	UPROPERTY() float previousShopRefreshTimer = 1.0f;

	UPROPERTY(EditAnywhere) TSubclassOf <AFarmActor> FarmActorClass;
	UPROPERTY() TArray<AFarmActor*> FarmActors;
	UPROPERTY(EditAnywhere) int baseFarmWoodPrice = 2;
	UPROPERTY(EditAnywhere) int baseFarmFoodPrice = 5;
	UPROPERTY(EditAnywhere) int baseFarmGoldPrice = 5;
	UFUNCTION(BlueprintCallable) int GetBaseFarmWoodPrice();
	UFUNCTION(BlueprintCallable) int GetBaseFarmFoodPrice();
	UFUNCTION(BlueprintCallable) int GetBaseFarmGoldPrice();

	UPROPERTY() int farmProductionAmount = 1;
	UPROPERTY() int farmPop = 0;
	UPROPERTY() int farmPopAllowance = 10;
	UFUNCTION(BlueprintCallable) void IncreaseFarmPopAmount();
	UFUNCTION(BlueprintCallable) void DecreaseFarmPopAmount();
	UFUNCTION(BlueprintCallable) int GetFarmPopAmount();
	UFUNCTION(BlueprintCallable) int GetFarmPopAllowanceAmount();
	UFUNCTION() void RecalculateFarmPopAllowance();
	UFUNCTION() bool bConstructFarmActor();


	UPROPERTY(EditAnywhere) TSubclassOf <ALumberActor> LumberActorClass;
	UPROPERTY() TArray<ALumberActor*> LumberActors;
	UPROPERTY(EditAnywhere) int baseLumberWoodPrice = 2;
	UPROPERTY(EditAnywhere) int baseLumberIronPrice = 4;
	UPROPERTY(EditAnywhere) int baseLumberGoldPrice = 5;
	UFUNCTION(BlueprintCallable) int GetBaseLumberWoodPrice();
	UFUNCTION(BlueprintCallable) int GetBaseLumberIronPrice();
	UFUNCTION(BlueprintCallable) int GetBaseLumberGoldPrice();

	UPROPERTY() int lumberProductionAmount = 1;
	UPROPERTY() int lumberPop = 0;
	UPROPERTY() int lumberPopAllowance = 10;
	UFUNCTION(BlueprintCallable) void IncreaseLumberPopAmount();
	UFUNCTION(BlueprintCallable) void DecreaseLumberPopAmount();
	UFUNCTION(BlueprintCallable) int GetLumberPopAmount();
	UFUNCTION(BlueprintCallable) int GetLumberPopAllowanceAmount(); 
	UFUNCTION() void RecalculateLumberPopAllowance();
	UFUNCTION() bool bConstructLumberActor();


	UPROPERTY(EditAnywhere) TSubclassOf <AMineActor> MineActorClass;
	UPROPERTY() TArray<AMineActor*> MineActors;
	UPROPERTY(EditAnywhere) int baseMineWoodPrice = 4;
	UPROPERTY(EditAnywhere) int baseMineIronPrice = 2;
	UPROPERTY(EditAnywhere) int baseMineGoldPrice = 5;
	UFUNCTION(BlueprintCallable) int GetBaseMineWoodPrice();
	UFUNCTION(BlueprintCallable) int GetBaseMineIronPrice();
	UFUNCTION(BlueprintCallable) int GetBaseMineGoldPrice();

	UPROPERTY() int mineProductionAmount = 1;
	UPROPERTY() int minePop = 0;
	UPROPERTY() int minePopAllowance = 10;
	UFUNCTION(BlueprintCallable) void IncreaseMinePopAmount();
	UFUNCTION(BlueprintCallable) void DecreaseMinePopAmount();
	UFUNCTION(BlueprintCallable) int GetMinePopAmount();
	UFUNCTION(BlueprintCallable) int GetMinePopAllowanceAmount();
	UFUNCTION() void RecalculateMinePopAllowance();
	UFUNCTION() bool bConstructMineActor();
};
