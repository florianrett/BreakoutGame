// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutPlayerController.h"
#include "Paddle.h"

ABreakoutPlayerController::ABreakoutPlayerController()
{
	
}

void ABreakoutPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MovePaddle"), this, &ABreakoutPlayerController::HandleMovementInput);
}

void ABreakoutPlayerController::SetControlledPaddle(APaddle* Paddle)
{
	ControlledPaddle = Paddle;
}

void ABreakoutPlayerController::HandleMovementInput(float AxisValue)
{
	if (ControlledPaddle)
	{
		ControlledPaddle->SetMovementInput(AxisValue);
	}
}
