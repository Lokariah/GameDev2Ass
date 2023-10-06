// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IdleGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEV2ASS_API AIdleGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:

	//Ensures player can interact with Main Menu.
	virtual void BeginPlay() override;
};
