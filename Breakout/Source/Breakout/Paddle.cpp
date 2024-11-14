// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PaddleSize = FVector2D(100.0f, 50.0f);
	MaxLaunchAngle = 45.0f;
	MovementSpeed = 500.0f;

	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Collider;
}

void APaddle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Collider->SetBoxExtent(FVector(PaddleSize.X, 50.f, PaddleSize.Y));
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Paddle Movement
	FVector TargetPos = GetActorLocation() + FVector(CurrentMovementInput * DeltaTime * MovementSpeed, 0.0f, 0.0f);
	SetActorLocation(TargetPos, true);
}

FVector2D APaddle::GetNewVelocity_Implementation(const FVector2D& CurrentVelocity, const FHitResult& Hit)
{
	// Set the new direction based on impact location along the paddle
	const float Speed = CurrentVelocity.Length();
	const FVector ImpactRelative = Hit.ImpactPoint - GetActorLocation();
	const float NormalizedImpact = ImpactRelative.X / PaddleSize.X;
	
	const FVector2D NewDirection = FVector2D(0.0f, 1.0f).GetRotated(NormalizedImpact * MaxLaunchAngle * -1.0f);

	return NewDirection * Speed;
}

void APaddle::SetMovementInput(float MovementInput)
{
	CurrentMovementInput = MovementInput;
}

