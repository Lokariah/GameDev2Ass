// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IdleGameInstance.h"
#include "BuildingPlacementActor.generated.h"

UCLASS()
class GAMEDEV2ASS_API ABuildingPlacementActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingPlacementActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnSelected(AActor* Target, FKey ButtonPressed);
	UPROPERTY()
		UIdleGameInstance* gameInstanceRef;
	UPROPERTY()
		bool selected = false;
	UPROPERTY()
		float rotationAmount = 0.0f;
	UFUNCTION()
		void Unselect();
};
