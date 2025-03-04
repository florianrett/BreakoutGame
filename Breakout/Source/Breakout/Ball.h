// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/UnitConversion.h"
#include "Ball.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBallLostDelegate, const ABall*, Ball);

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

	UPROPERTY(BlueprintAssignable)
	FBallLostDelegate OnBallLost;

	// Set the ball's velocity to a specific value
	UFUNCTION(BlueprintCallable)
	void SetVelocity(const FVector2D& NewVelocity);

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const
	{
		return Velocity.Length();
	}

protected:
	// Move the ball for DeltaSeconds seconds
	void MoveBall(float DeltaSeconds);

	// Determine whether the ball is lost and needs to be destroyed
	UFUNCTION(BlueprintNativeEvent)
	bool CheckBallDestruction();
	
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
