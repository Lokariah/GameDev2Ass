// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingPlacementActor.h"
#include "IdleGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "FarmActor.generated.h"

UCLASS()
class GAMEDEV2ASS_API AFarmActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnSelected(AActor* Target, FKey ButtonPressed);
	UFUNCTION() void StoreBuildingPlacementActor(ABuildingPlacementActor* ref);
	UPROPERTY() UIdleGameInstance* gameInstanceRef;
private:
	ABuildingPlacementActor* originalActor;

	UPROPERTY() int currentTierLvl = 1;
	UPROPERTY() float timeCount = 0.0f;

	UPROPERTY(EditAnywhere) int baseFoodProductionAmount = 1;
	UPROPERTY(EditAnywhere) int baseFoodProductionRate = 60;
	UPROPERTY(EditAnywhere) int baseFoodSellPrice = 10;

	UPROPERTY(EditAnywhere) int tier2WoodUpgradePrice = 4;
	UPROPERTY(EditAnywhere) int tier2GoldUpgradePrice = 10;
	UPROPERTY(EditAnywhere) int tier2FoodProductionAmount = 2;
	UPROPERTY(EditAnywhere) int tier2FoodProductionRate = 30;
	UPROPERTY(EditAnywhere) int tier2FoodSellPrice = 15;

	UPROPERTY(EditAnywhere) int tier3WoodUpgradePrice = 8;
	UPROPERTY(EditAnywhere) int tier3GoldUpgradePrice = 20;
	UPROPERTY(EditAnywhere) int tier3FoodProductionAmount = 4;
	UPROPERTY(EditAnywhere) int tier3FoodProductionRate = 15;
	UPROPERTY(EditAnywhere) int tier3FoodSellPrice = 25;

};
