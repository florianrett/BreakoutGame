// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BreakoutPlayerController.generated.h"

class APaddle;

/**
 * 
 */
UCLASS()
class BREAKOUT_API ABreakoutPlayerController : public APlayerController
{
	GENERATED_BODY()
	ABreakoutPlayerController();

public:
	void SetControlledPaddle(APaddle* Paddle);

private:
	UPROPERTY()
	TObjectPtr<APaddle> ControlledPaddle;
	
};
