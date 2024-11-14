// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallCollision.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Paddle.generated.h"

UCLASS()
class BREAKOUT_API APaddle : public AActor, public IBallCollision
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaddle();

	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//------------------------------
	// Override IBallCollision
	//------------------------------
	virtual FVector2D GetNewVelocity_Implementation(const FVector2D& CurrentVelocity, const FHitResult& Hit) override;
	//------------------------------
	// ~End Override IBallCollision
	//------------------------------

	// Set current movement input for the paddle
	void SetMovementInput(float MovementInput);

protected:
	// The paddle's collider
	UPROPERTY()
	TObjectPtr<UBoxComponent> Collider;
	
	// Size of the paddle
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D PaddleSize;

	// Speed the paddle moves at
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	// The maximum angle the paddle can launch off balls
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin="0.0", ClampMax="89.9"))
	float MaxLaunchAngle;

	float CurrentMovementInput = 0;
};
