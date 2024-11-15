// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallCollision.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlockDestroyedDelegate, const ABlock*, DestroyedBlock);

UCLASS()
class BREAKOUT_API ABlock : public AActor, public IBallCollision
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	//------------------------------
	// Override IBallCollision
	//------------------------------
	// Calculate the ball's new velocity after colliding with this block
	virtual FVector2D GetNewVelocity_Implementation(const FVector2D& CurrentVelocity, const FHitResult& Hit) const override;
	// Called when the block is hit by a ball
	virtual void ProcessHit_Implementation() override;
	//------------------------------
	// ~End Override IBallCollision
	//------------------------------

	int32 GetScore() const
	{
		return ScoreValue;
	}

	UPROPERTY(BlueprintAssignable)
	FBlockDestroyedDelegate OnBlockDestroyed;

protected:
	// BP event for when a block is destroyed to allow easy access for VFX, SFX, etc.
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnBlockDestroyed();

	// The block's score value when destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ScoreValue;
	

};
