// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Components/BoxComponent.h"

ABlock::ABlock(const FObjectInitializer& ObjectInitializer)
{
	// Disable actor tick for all blocks to improve performance
	PrimaryActorTick.bCanEverTick = false;

	TObjectPtr<UBoxComponent> Collider = CreateDefaultSubobject<UBoxComponent>(FName("Collider"));
	Collider->SetCollisionProfileName(FName("BlockAll"));
	Collider->SetBoxExtent(FVector(50, 50, 50));
	RootComponent = Collider;
}

FVector2D ABlock::GetNewVelocity_Implementation(const FVector2D& CurrentVelocity, const FHitResult& Hit)
{
	// Mirror velocity along the impact normal
	FVector2D Normal2D = FVector2D(Hit.ImpactNormal.X, Hit.ImpactNormal.Z);
	float Dot = Normal2D.Dot(CurrentVelocity);
	ensure(Dot <= 0);// Positive dot product would indicate a collision from within the object, which should never happen
	return CurrentVelocity + Normal2D * -2.0f * Dot;
}
