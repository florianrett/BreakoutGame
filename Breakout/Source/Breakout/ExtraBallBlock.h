// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ball.h"
#include "Block.h"
#include "ExtraBallBlock.generated.h"

/**
 * A special type of block that spawns an additional ball when destroyed
 */
UCLASS()
class BREAKOUT_API AExtraBallBlock : public ABlock
{
	GENERATED_BODY()
public:
	AExtraBallBlock();

	// Called when the block is hit by a ball
	virtual void ProcessHit_Implementation() override;

protected:
	// The class of the new ball to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABall> BallClass;

	// Speed the spawned ball should be travelling at. Disable to use its class default
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bOverrideSpeed"))
	float BallSpeed;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle));
	bool bOverrideSpeed;
	
	
};
