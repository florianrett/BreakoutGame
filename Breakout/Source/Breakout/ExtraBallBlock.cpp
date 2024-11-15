// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraBallBlock.h"
#include "BreakoutGameMode.h"

AExtraBallBlock::AExtraBallBlock()
{
	ScoreValue = 10;
}

void AExtraBallBlock::ProcessHit_Implementation()
{
	Super::ProcessHit_Implementation();

	if (ABreakoutGameMode* GameMode = Cast<ABreakoutGameMode>(GetWorld()->GetAuthGameMode()))
	{
		// Spawn a new ball
		if (IsValid(BallClass))
		{
			const FVector BallLocation = GetActorLocation();
			if (ABall* NewBall = Cast<ABall>(GetWorld()->SpawnActor(BallClass, &BallLocation)))
			{
				const float Speed = bOverrideSpeed ? BallSpeed : NewBall->GetSpeed();
				const FVector2D RandomVelocity = FVector2D(Speed, 0.0f).GetRotated(FMath::FRand() * 360);
				NewBall->SetVelocity(RandomVelocity);

				// Register the ball with the GameMode
				GameMode->AddBall(NewBall);
			}
			
		}
	}
}
