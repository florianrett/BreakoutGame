// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutPlayerController.h"
#include "Paddle.h"

ABreakoutPlayerController::ABreakoutPlayerController()
{
	
}

void ABreakoutPlayerController::SetControlledPaddle(APaddle* Paddle)
{
	ControlledPaddle = Paddle;
}
