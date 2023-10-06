// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPlacementActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABuildingPlacementActor::ABuildingPlacementActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnClicked.AddUniqueDynamic(this, &ABuildingPlacementActor::OnSelected);
}

// Called when the game starts or when spawned
void ABuildingPlacementActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingPlacementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (selected) {
		AddActorLocalRotation(FQuat(this->GetActorQuat().GetAxisZ(), -DeltaTime));
		rotationAmount += DeltaTime;
	}
	else if (rotationAmount > 0.00001f) {
		AddActorLocalRotation(FQuat(this->GetActorQuat().GetAxisZ(), rotationAmount));
		rotationAmount -= rotationAmount;
	}
}

void ABuildingPlacementActor::OnSelected(AActor* Target, FKey ButtonPressed)
{
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstanceRef) {
		gameInstanceRef->SelectBuildableSpace(this);
		selected = true;
		if (gameInstanceRef->GetCurrentConstructMenuState() == ConstructMenuStates::Build) {
			if (gameInstanceRef->GetCurrentStructureType() == StructureTypes::Farm) {
				if (gameInstanceRef->bCheckFarmBuildability()) gameInstanceRef->FarmBuildTransaction();
			}
			else if (gameInstanceRef->GetCurrentStructureType() == StructureTypes::Lumber) {
				if (gameInstanceRef->bCheckLumberBuildability()) gameInstanceRef->LumberBuildTransaction();
			}
			else if (gameInstanceRef->GetCurrentStructureType() == StructureTypes::Mine) {
				if (gameInstanceRef->bCheckMineBuildability()) gameInstanceRef->MineBuildTransaction();
			}
		}
	}
}

void ABuildingPlacementActor::Unselect()
{
	selected = false;
}

