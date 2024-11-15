// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Components/SphereComponent.h"
#include "BallCollision.h"

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

void ABall::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveBall(DeltaSeconds);
	if (CheckBallDestruction())
	{
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
		OnBallLost.Broadcast(this);
		SetLifeSpan(2.0f);
		SetActorTickEnabled(false); // Disable further ticking while ball is being destroyed
	}
}

void ABall::SetVelocity(const FVector2D& NewVelocity)
{
	Velocity = NewVelocity;
}

void ABall::MoveBall(float DeltaSeconds)
{
	const FVector TargetLocation = GetActorLocation() + DeltaSeconds * FVector(Velocity.X, 0.0f, Velocity.Y);
	FHitResult Hit;
	// Sweep ball forward to check for collisions
	SetActorLocation(TargetLocation, true, &Hit);
	if (Hit.bBlockingHit)
	{
		if (Hit.GetActor()->Implements<UBallCollision>())
		{
			// If the hit object implements IBallCollision interface it can override the ball's new velocity
			Velocity = IBallCollision::Execute_GetNewVelocity(Hit.GetActor(), Velocity, Hit);

			// Notify the hit object so it can react accordingly
			IBallCollision::Execute_ProcessHit(Hit.GetActor());
		}
		else
		{
			// For all other objects, new direction is calculated following laws of physics by mirroring along the impact normal
			FVector2D Normal2D = FVector2D(Hit.ImpactNormal.X, Hit.ImpactNormal.Z);
			float Dot = Normal2D.Dot(Velocity);
			ensure(Dot <= 0);// Positive dot product would indicate a collision from within the object, which should never happen
			Velocity += Normal2D * -2.0f * Dot;
		}

		// Continue moving the ball for the remaining time
		if (const float RemainingTime = 1 - Hit.Time; RemainingTime > 0)
		{
			MoveBall(RemainingTime * DeltaSeconds);
		}
	}
}

bool ABall::CheckBallDestruction_Implementation()
{
	if (GetActorLocation().Z <= 0)
	{
		return true;
	}

	return false;
}
