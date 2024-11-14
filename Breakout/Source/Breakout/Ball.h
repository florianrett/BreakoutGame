// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class BREAKOUT_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	// Called every time a ball is constructed, both in editor and at runtime
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	// Move the ball for DeltaSeconds seconds
	void MoveBall(float DeltaSeconds);
	
	// The ball's radius. For reference, blocks have a default size of 100 units
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius;

	// Sphere component to handle ball collision
	UPROPERTY()
	TObjectPtr<class USphereComponent> Collider;

	// The balls current velocity
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Velocity;
};
