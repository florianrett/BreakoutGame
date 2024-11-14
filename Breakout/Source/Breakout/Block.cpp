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
