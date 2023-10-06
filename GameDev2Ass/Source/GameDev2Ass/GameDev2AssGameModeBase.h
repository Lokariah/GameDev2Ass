// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "IdleGameInstance.h"
#include "GameDev2AssGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV2ASS_API AGameDev2AssGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGameDev2AssGameModeBase();
	UPROPERTY() UIdleGameInstance* gameInstanceRef;
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	//UI
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MainMenuClass;
	UPROPERTY()
		UUserWidget* MainMenuCount;
};
