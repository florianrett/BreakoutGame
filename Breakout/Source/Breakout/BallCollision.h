// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BallCollision.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBallCollision : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects a ball can collide with.
 */
class BREAKOUT_API IBallCollision
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector2D GetNewDirection();
};
