// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameDev2AssGameModeBase.h"
#include "Blueprint/UserWidget.h"

AGameDev2AssGameModeBase::AGameDev2AssGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void AGameDev2AssGameModeBase::BeginPlay() {
	Super::BeginPlay();
	MainMenuCount = CreateWidget(GetWorld(), MainMenuClass);
	if (MainMenuCount) MainMenuCount->AddToViewport();
}

void AGameDev2AssGameModeBase::Tick(float DeltaSeconds)
{
	gameInstanceRef = Cast<UIdleGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameInstanceRef) gameInstanceRef->TimeTick(DeltaSeconds);
}
