// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IdleGameInstance.h"
#include "BuildingPlacementActor.h"
#include "Kismet/GameplayStatics.h"
#include "MineActor.generated.h"

UCLASS()
class GAMEDEV2ASS_API AMineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnSelected(AActor* Target, FKey ButtonPressed);
	UFUNCTION() void StoreBuildingPlacementActor(ABuildingPlacementActor* ref);
	UPROPERTY()
		UIdleGameInstance* gameInstanceRef;
private:
	ABuildingPlacementActor* originalActor;

	UPROPERTY() int currentTierLvl = 1;
	UPROPERTY() float timeCount = 0.0f;

	UPROPERTY(EditAnywhere) int baseMineProductionAmount = 1;
	UPROPERTY(EditAnywhere) int baseMineProductionRate = 60;
	UPROPERTY(EditAnywhere) int baseMineSellPrice = 10;

	UPROPERTY(EditAnywhere) int tier2IronUpgradePrice = 4;
	UPROPERTY(EditAnywhere) int tier2GoldUpgradePrice = 10;
	UPROPERTY(EditAnywhere) int tier2MineProductionAmount = 2;
	UPROPERTY(EditAnywhere) int tier2MineProductionRate = 30;
	UPROPERTY(EditAnywhere) int tier2MineSellPrice = 15;

	UPROPERTY(EditAnywhere) int tier3IronUpgradePrice = 8;
	UPROPERTY(EditAnywhere) int tier3GoldUpgradePrice = 20;
	UPROPERTY(EditAnywhere) int tier3MineProductionAmount = 4;
	UPROPERTY(EditAnywhere) int tier3MineProductionRate = 15;
	UPROPERTY(EditAnywhere) int tier3MineSellPrice = 25;
};
