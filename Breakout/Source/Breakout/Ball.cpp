// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Components/SphereComponent.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	Radius = 20.f;

	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));
	Collider->SetCollisionProfileName(TEXT("Ball"));
	RootComponent = Collider;
}

void ABall::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Collider->SetSphereRadius(Radius);
}
