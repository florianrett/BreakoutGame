// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutGameMode.h"

#include "Ball.h"
#include "Block.h"
#include "BreakoutPlayerController.h"
#include "EngineUtils.h"
#include "Paddle.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/MenuGameMode.h"

ABreakoutGameMode::ABreakoutGameMode(const FObjectInitializer& FObjectInitializer) : Super(FObjectInitializer)
{
	PlayerControllerClass = ABreakoutPlayerController::StaticClass();
}

void ABreakoutGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Setup game UI
	if (IsValid(GameWidgetClass))
	{
		GameWidget = CreateWidget<UGameWidget>(GetWorld(), GameWidgetClass, FName(TEXT("GameWidget")));
		if (GameWidget)
		{
			GameWidget->SetButtonVisibility(false);
			GameWidget->SetScore(0);
			GameWidget->AddToViewport();
			GameWidget->RestartButton->OnClicked.AddDynamic(this, &ABreakoutGameMode::RestartGame);
			GameWidget->ExitButton->OnClicked.AddDynamic(this, &ABreakoutGameMode::ExitGame);
			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameWidgetClass is not set!"));
	}

	// Find all camera actors in the current level and cache them as potential view targets
	for (TActorIterator<ACameraActor> It(GetWorld(), ACameraActor::StaticClass()); It; ++It)
	{
		Cameras.Add(*It);
	}

	CycleCamera();

	// Setup and start the game
	SetupBlocks();
	SetupPaddle();
}

void ABreakoutGameMode::SetupBlocks_Implementation()
{
	for (TActorIterator<ABlock> It(GetWorld(), ABlock::StaticClass()); It; ++It)
	{
		RegisterBlock(*It);
	}

	if (Blocks.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("There are no blocks to the level, either add at least one block or override ABreakoutGameMode::SetupBlocks!"));
	}
}

void ABreakoutGameMode::SetupBalls_Implementation()
{
	for (TActorIterator<ABall> It(GetWorld(), ABall::StaticClass()); It; ++It)
	{
		AddBall(*It);
	}

	if (Balls.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("There are no balls to the level, either add at least one ball or override ABreakoutGameMode::SetupBalls!"));
	}
}

void ABreakoutGameMode::RegisterBlock(ABlock* Block)
{
	Blocks.Add(Block);
}

void ABreakoutGameMode::SetupPaddle_Implementation()
{
	APaddle* Paddle = nullptr;
	for (TActorIterator<APaddle> It(GetWorld(), APaddle::StaticClass()); It; ++It)
	{
		Paddle = *It;
		break; //
	}
	if (!Paddle)
	{
		UE_LOG(LogTemp, Error, TEXT("There is no paddle the level, either add a paddle or override ABreakoutGameMode::SetupPaddle!"));
		return;
	}

	if (ABreakoutPlayerController* PlayerController = Cast<ABreakoutPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->SetControlledPaddle(Paddle);
	}
}

void ABreakoutGameMode::AddBall(ABall* Ball)
{
	Balls.Add(Ball);
}

void ABreakoutGameMode::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(this)), false);
}

void ABreakoutGameMode::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void ABreakoutGameMode::CycleCamera()
{
	if (Cameras.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("There are no CameraActors in the current level!"));
		return;
	}
	CurrentCameraIndex += 1;
	CurrentCameraIndex %= Cameras.Num();

	GetWorld()->GetFirstPlayerController()->SetViewTarget(Cameras[CurrentCameraIndex]);
}
