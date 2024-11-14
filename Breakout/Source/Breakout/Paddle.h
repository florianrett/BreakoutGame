// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Paddle.generated.h"

UCLASS()
class BREAKOUT_API APaddle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaddle();

	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// The paddle's collider
	UPROPERTY()
	TObjectPtr<UBoxComponent> Collider;
	
	// Size of the paddle
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D PaddleSize;

};
